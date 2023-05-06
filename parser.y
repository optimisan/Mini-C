%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "./util/AST.h"
#include "./util/symbol.h"
#include "./util/token.h"
#include "./backend/backend.h"

char *currentFileName;
Type* currentFunctionType;
extern int level;
extern int lineno, col;
int templineno, tempcol;

int yyerror(char *s);
Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...);
void compileError(Coordinate pos, int lexemeLength, char *format, ...);
void errorMessage(Coordinate pos, int lexemeLength, char *format, ...);
int typeCheckAssign(TypeEnum t1, TypeEnum t2);
void typeCheckUnary(Node* t);
void typeCheckArrayInitialiser(Type* elementType, Node* expr);

Node* param_list_node, *funcBodyNode;
int yylex();
%}

%union {
    int iValue;
    float fValue;
    char* sValue;
    IdStruct id;
    char cValue;
    Node* node;
};

/* Keywords */
%token <iValue> K_INT K_FLOAT K_CHAR 
%token FOR WHILE ELSE IF SWITCH CASE RETURN CONTINUE BREAK DEFAULT
/* Literals */
%token <iValue> INTEGER 
%token <fValue> FLOAT
%token <cValue> CHARACTER
%token <sValue> STRING
/* Assignments */
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN 

/* Comparison */
/* %token EQ LE GE NE */
/* Logical */
/* %token AND OR */
/* Symbols */
/* %token  */
/* Comments */
/* %token SINGLE_START MULTI_START MULTI_END */
/* Brackets */
/* %token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET */

%token <id> IDENTIFIER 
%token ERROR

%token EOF_TOKEN

%nonassoc IFX
%nonassoc ELSE

%left AND OR
%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
/* Math op */
%token INC DEC
%nonassoc UMINUS
%left '[' ']'
%nonassoc ARR

%type <node> expr arrayExpr callExpr arg_list continueStmt breakStmt returnStmt varInitialiser varNames arraySpecifier varDeclaration arrayInitialiser array_init_list param_list functionDecl declarations declaration funcBody stmtOrDecl stmt assignExpr switchStmt switchBody switchList caseLabel whileStmt blockStmt ifStmt forStmt forInit forCond forIter
%type <iValue> varType funcArraySpecifier
/* %t declarations declaration functionDecl param_list varInitialiser varDeclaration varType varNames arraySpecifier funcBody stmtOrDecl stmt assignExpr switchStmt switchBody switches cases caseLabel caseType whileStmt blockStmt ifStmt expr arrayExpr callExpr returnStmt continueStmt breakStmt arg_list */

%%

program: declarations EOF_TOKEN { 
                        // printf("Program end\n"); 
                        backend($1, currentFileName);
                        return 0;
                    }
    ;

declarations: declarations declaration { $$ = oprNode(OPR_DECL_LIST, 2, $1, $2); }
    | {$$ = NULL;}
    ;

declaration: functionDecl
    | functionDecl ';'
    /* | varDeclaration ';' */
    ;

functionDecl: varType IDENTIFIER {
                        Symbol* funcSymbol = install($2.name, &identifiers, level, $2.src);
                        if(funcSymbol->type){
                            errorMessage($2.src, strlen($2.name), ANSI_COLOR_BOLD ANSI_COLOR_CYAN "Note: " ANSI_COLOR_RESET "Function '%s' already declared", $2.name);
                            compileError(funcSymbol->src, strlen($2.name), "Declared here:");
                        }
                        beginScope();
                        }
            '(' param_list ')' 
                        {
                            Type* funcType = malloc(sizeof(Type));
                            funcType->sym = NULL;
                            funcType->op = T_FUNCTION;
                            funcType->type = malloc(sizeof(Type));
                            funcType->type->op = $1;
                            currentFunctionType = funcType;
                        }
            funcBody
                {
                    endScope();
                    Symbol* funcSymbol = install($2.name, &identifiers, level, $2.src);
                            // Type* funcType = malloc(sizeof(Type));
                            // funcType->sym = funcSymbol;
                            // funcType->op = T_FUNCTION;
                            // funcType->type = malloc(sizeof(Type));
                            // funcType->type->op = $1;
                            // currentFunctionType = funcType;
                            Type* funcType = currentFunctionType;
                            funcSymbol->type = currentFunctionType;
                            int numParams=0;
                            Node* temp = $5;
                            while(temp){
                                numParams++;
                                if(temp->as.opr.nops == 2)
                                    temp = temp->as.opr.operands[0];
                                else temp = NULL;
                            }
                            funcType->size = numParams;
                            funcType->proto = malloc(sizeof(Type*) * numParams);
                            Node* param = $5;
                            int i=0;
                            // printf("donefg %d\n", numParams);
                            while(param){
                                if(param->as.opr.nops == 2){
                                    //last param
                                    // printf("Type of param is %d\n", param->as.opr.operands[0]->type);
                                    funcType->proto[i] = param->as.opr.operands[1]->as.symbol->type;
                                } else {
                                    funcType->proto[i] = param->as.opr.operands[0]->as.symbol->type;
                                }
                                i++;
                                if(param->as.opr.nops == 2)
                                    param = param->as.opr.operands[0];
                                else param = NULL;
                            }
                            // if(funcType->proto)
                            // printf("func proto %d\n",1/* ,  funcType->proto[0]->op */);
                    // Symbol* funcSymbol = lookup($2.name, identifiers);
                    // printNode(param_list_node);
                    $<node>$ = oprNode(OPR_FUNC, 3, identifierNode(funcSymbol), param_list_node, funcBodyNode);
                    currentFunctionType = NULL;
                }
                ;
funcArraySpecifier: '['']' {$$=1;} | {$$=0;} ;
param_list: varType IDENTIFIER funcArraySpecifier {
                        Symbol* psym = install($2.name, &identifiers, level, $2.src);
                        $$ = oprNode(OPR_LIST, 1, identifierNode(psym)); 
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = $1;
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        if($3){
                            psym->type = newType(T_ARRAY);
                            psym->type->type = paramType;
                            psym->type->sym = psym;
                        }
                        param_list_node = $$;
                    }
    | param_list ',' varType IDENTIFIER funcArraySpecifier {
                        Symbol* psym = install($4.name, &identifiers, level, $4.src);
                        if(psym->type){
                            compileError($4.src, strlen($4.name), "Parameter %s already declared", $4.name);
                        }
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = $3;
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        if($5){
                            psym->type = newType(T_ARRAY);
                            psym->type->type = paramType;
                            psym->type->sym = psym;
                        }
                        $$ = oprNode(OPR_LIST, 2, $1, identifierNode(psym));
                        param_list_node = $$;
                    }
    | {$$=NULL; param_list_node = NULL;}
    ;
//int arr[10][20] = {1,2,3,4};
varInitialiser: IDENTIFIER arraySpecifier {
                                    $$ = oprNode('=', 2, identifierNode(install($1.name, &identifiers, level, $1.src)), $2);
                                    $$->src = $1.src;
                                    }
    | IDENTIFIER arraySpecifier '=' expr {
                                    $$ = oprNode('=', 3, identifierNode(install($1.name, &identifiers, level, $1.src)), $2, $4);
                                    $$->src = $1.src;
                                    }
    | IDENTIFIER arraySpecifier '=' arrayInitialiser {$$ = oprNode('=', 3, identifierNode(install($1.name, &identifiers, level, $1.src)), $2, $4); $$->src = $1.src;}

arrayInitialiser: '{' array_init_list '}' { $$ = $2; $$->exprType.op = T_ARRAY;}

array_init_list: expr { /* $$ = oprNode(OPR_LIST, 1, $1); */}
    | array_init_list ',' expr { $$ = oprNode(OPR_LIST, 3, $1, $3, NULL); }
    | arrayInitialiser { /* $$ = oprNode(OPR_LIST, 1, $1); */$$ = $1; $$->exprType.op = T_ARRAY;}
    | array_init_list ',' arrayInitialiser { $$ = oprNode(OPR_LIST, 3, $1, $3, NULL); $$->exprType.op = T_ARRAY;}
    ;

/* expr_list: expr
    | expr_list ',' expr
    |
    ; */

varDeclaration: varType varNames {
    $$ = oprNode(OPR_VAR_DECL, 1, $2);
    // printf("Found var decl %d, \n", $2->as.opr.type);
    //iterate through the list of variables and add them to the symbol table
    Node* varName = $2;
    while(varName != NULL) {
        Node* varInitialiser;
        if(varName->as.opr.type == OPR_LIST) {
            varInitialiser = varName->as.opr.operands[1];
            // printf("Found list %d\n", varInitialiser->as.opr.type);
        } else {
            varInitialiser = varName;
        }
        // printf("Found var decl for '%s', \n", varInitialiser->as.opr.operands[0]->as.symbol->name);
        Symbol* varSymbol = varInitialiser->as.opr.operands[0]->as.symbol;
        Symbol* installed = install(varSymbol->name, &identifiers, level, varSymbol->src);
        Coordinate src = varSymbol->src;
        if(installed->type){
            errorMessage(varInitialiser->src, strlen(varSymbol->name), ANSI_COLOR_BOLD ANSI_COLOR_CYAN "Note: " ANSI_COLOR_RESET "Variable '%s' already declared", varSymbol->name);
            compileError(varSymbol->src, strlen(varSymbol->name), "Declared here");
        }
        Type* type = malloc(sizeof(Type));
        type->sym = installed;
        installed->type = type;
        type->op = $1;
        int arrLastSize = -1;
        //check if this is an array
        if(varInitialiser->as.opr.operands[1] != NULL){
            Node* arraySpecifier = varInitialiser->as.opr.operands[1];
            Type* outerType = type;
            do {
                arrLastSize = arraySpecifier->as.opr.operands[1]->as.value->as.integer;
                //check if size is declared for dimensions other than first
                if(arrLastSize <= 0 && arraySpecifier->as.opr.operands[0] != NULL){
                    compileError(src, strlen(varSymbol->name), "Array dimensions except the first cannot be empty %d", arrLastSize);
                }
                Type* innerType = malloc(sizeof(Type));
                outerType->sym = installed;
                outerType->op = T_ARRAY;
                outerType->size = arrLastSize;
                outerType->type = innerType;
                outerType = innerType;
            } while((arraySpecifier = arraySpecifier->as.opr.operands[0]));
            outerType->sym = installed;
            outerType->op = $1;
            outerType->size = arrLastSize;
            // installed->type=outerType;
            // printf("Innermost type is %d\n", outerType->op);
        }

        // printf("\nType op of this var is %d\n", installed->type->op);
        
        //Check if there is an initialiser expression assignment
        if(varInitialiser->as.opr.nops == 3){
            Node* expr = varInitialiser->as.opr.operands[2];
            // printf("Found initialiser %d\n", expr->exprType);
            if(!typeCheckAssign(installed->type->op, expr->exprType.op)){
                compileError(src, strlen(varSymbol->name), "Type mismatch in variable initialisation of '%s'", varSymbol->name);
            }
            //Check if string initialiser
            if(expr->type == NODE_LITERAL && expr->as.value->type == T_ARRAY){
                if(installed->type->op != T_ARRAY || installed->type->type->op != T_CHAR){
                    compileError(src, strlen(varSymbol->name), "Type mismatch (string must be char[]) in variable initialisation %s", varSymbol->name);
                }
            }
            //Check if the initialiser is an array
            if(expr->as.opr.type == OPR_LIST){
                //check every element type
                typeCheckArrayInitialiser(installed->type, expr);
            }

        }
        //Move forward to the next variable
        if(varName->as.opr.type == OPR_LIST){
            varName = varName->as.opr.operands[0];
        } else {
            varName = NULL;
        }
    }
}
;

varType: K_INT {$$ = T_INT;} | K_CHAR {$$ = T_CHAR;}| K_FLOAT {$$ = T_FLOAT;};

varNames: varInitialiser 
    | varNames ',' varInitialiser {$$ = oprNode(OPR_LIST, 2, $1, $3); }

arraySpecifier: arraySpecifier '[' INTEGER ']' {
                                        $$ = oprNode(OPR_LIST, 2, $1, intNode($3));
                                    }
    | arraySpecifier '[' ']' {
                            $$ = oprNode(OPR_LIST, 2, $1, intNode(0));
                        }
    | { $$ = NULL; }
    ;

funcBody: '{' {$<node>$ = NULL;}
            stmtOrDecl
          '}' { $$ = $3;}
          ;

stmtOrDecl: stmtOrDecl stmt {$$ = oprNode(OPR_LIST, 2, $1, $2); funcBodyNode = $$;}
    | stmtOrDecl varDeclaration ';' {$$ = oprNode(OPR_LIST, 2, $1, $2); funcBodyNode = $$;}
    | {$$ = NULL; funcBodyNode = $$;}
    ;


/* stmtList: stmtList stmt */
    /* |
    ; */

stmt: ';' {$$ = NULL;}
    | blockStmt 
    /* | varDeclaration ';' */
    | assignExpr ';'
    /* | expr ';' */
    | callExpr ';'
    | ifStmt
    | whileStmt
    | forStmt
    | switchStmt
    | returnStmt ';'
    | breakStmt ';'
    | continueStmt ';'
    ;

forStmt: FOR '(' {beginScope();} forInit ';' forCond ';' forIter ')' stmt {
    endScope();
    $$ = oprNode(OPR_FOR, 4, $4, $6, $8, $10);
}

forInit: assignExpr
    | varDeclaration
    | {$$ = NULL;}
    ;

forCond: expr
    | {$$ = NULL;}
    ;

forIter: assignExpr
    | {$$=NULL;}
    ;

assignExpr: IDENTIFIER '=' expr {
                // printf("Found assign target\n");
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                if(!typeCheckAssign(sym->type->op, $3->exprType.op)){
                    compileError($1.src, strlen($1.name), "Type mismatch in assignment %s", $1.name);
                }
                $$ = oprNode(OPR_ASSIGN, 2, identifierNode(sym), $3);
            }
    | IDENTIFIER INC {
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                compileError((Coordinate){lineno, col-2}, 2, "Increment operator not allowed");
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError($1.src, strlen($1.name), "Only int and float can be incremented %s", $1.name);
                }
                $$ = oprNode(OPR_INC, 1, identifierNode(sym));
            }
    | IDENTIFIER DEC {
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                compileError((Coordinate){lineno, col-2}, 2, "Decrement operator not allowed");
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError($1.src, strlen($1.name), "Only int and float can be decremented %s", $1.name);
                }
                $$ = oprNode(OPR_DEC, 1, identifierNode(sym));
            }
    | arrayExpr '=' expr {
                // printf("Got array type as %d = %d\n", $1->exprType.op, $3->exprType.op);
                if(!typeCheckAssign($1->exprType.op, $3->exprType.op)){
                    compileError($1->src, $3->src.length + $1->src.length, "Type mismatch in assignment to array");
                }
                $$ = oprNode(OPR_ASSIGN, 2, $1, $3);
            }
    | arrayExpr INC {
                if($1->exprType.op != T_INT && $1->exprType.op != T_FLOAT){
                    compileError($1->src, $1->src.length + 2, "Only int and float can be incremented");
                }
                $$ = oprNode(OPR_INC, 1, $1);
            }
    | arrayExpr DEC {
                if($1->exprType.op != T_INT || $1->exprType.op != T_FLOAT){
                    compileError($1->src, $1->src.length+2, "Only int and float can be decremented");
                }
                $$ = oprNode(OPR_DEC, 1, $1);
            }
    ;

switchStmt: 
    SWITCH          { errorMessage((Coordinate){lineno, col-6, 0}, 6, 
                                    ANSI_COLOR_BOLD ANSI_COLOR_BLUE 
                                    "Warning: " ANSI_COLOR_RESET "Switch statement is not implemented");
                    }
    '(' expr ')' {beginScope();} '{' switchBody '}' { $$ = NULL; endScope();}
switchBody: switchList | {$$ = NULL;};
switchList: stmt
    | varDeclaration
    | caseLabel
    | switchList caseLabel
    | switchList stmt
    | switchList varDeclaration
    ;

/* switches: cases 
    |
    ; */

/* cases: caseLabel stmtList
    | cases caseLabel stmtList
    ; */

caseLabel: CASE {templineno = lineno; tempcol = col- 4;} expr ':' {
                if($3->type!= NODE_LITERAL){
                    compileError((Coordinate){templineno, tempcol, 0}, $3->src.length + 5, "Case label must be a constant");
                }
                if($3->exprType.op != T_INT){
                    compileError((Coordinate){templineno, tempcol, 0}, $3->src.length+5, "Case label must be an integer");
                }
} 
 | DEFAULT ':' {$$ = NULL;}
;

whileStmt: WHILE '(' expr ')' stmt {$$ = oprNode(OPR_WHILE, 2, $3, $5);}

blockStmt: '{'          {beginScope();}
            stmtOrDecl 
           '}'
                        {endScope(); $$ = $3;}
            ;

ifStmt: IF '(' expr ')' stmt %prec IFX { $$ = oprNode(OPR_IF, 2, $3, $5);}
    | IF '(' expr ')' stmt ELSE stmt { $$ = oprNode(OPR_IF, 3, $3, $5, $7);}

expr: INTEGER {$$ = intNode($1);}
    | CHARACTER {$$ = charNode($1); }
    | IDENTIFIER { 
            Symbol* foundId = getSymbol($1.name, identifiers, $1.src, "Identifier '%s' not declared in this scope", $1.name);
            $$ = identifierNode(foundId);
        }
    | FLOAT {$$ = floatNode($1);}
    | STRING {$$ = strNode($1, strlen($1));}
    | callExpr {$$ = $1;}
    | '-' expr %prec UMINUS { $$ = oprNode('-', 1, $2); typeCheckUnary($2); $$->exprType.op = $2->exprType.op;}
    | '!' expr %prec UMINUS { $$ = oprNode('!', 1, $2); typeCheckUnary($2); $$->exprType.op = $2->exprType.op;}
    | expr '+' expr { $$ = oprNode('+', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '-' expr { $$ = oprNode('-', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '*' expr { $$ = oprNode('*', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '/' expr { $$ = oprNode('/', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '<' expr { $$ = oprNode('<', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '>' expr { $$ = oprNode('>', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '%' expr { $$ = oprNode('%', 2, $1, $3);     $$->exprType.op = T_INT; if($1->exprType.op != T_INT || $3->exprType.op != T_INT){compileError($1->src, $1->src.length + $3->src.length, "Modulo operator only works on integers");}}
    | expr GE expr { $$ = oprNode(OPR_GE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr LE expr { $$ = oprNode(OPR_LE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr EQ expr { $$ = oprNode(OPR_EQ, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr NE expr { $$ = oprNode(OPR_NE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr AND expr { $$ = oprNode(OPR_AND, 2, $1, $3); $$->exprType.op = T_INT;if($1->exprType.op != T_INT || $3->exprType.op != T_INT){compileError($1->src, $1->src.length + $3->src.length, "Boolean operators only work on integers");}}
    | expr OR expr { $$ = oprNode(OPR_OR, 2, $1, $3);   $$->exprType.op = T_INT;if($1->exprType.op != T_INT || $3->exprType.op != T_INT){compileError($1->src, $1->src.length + $3->src.length, "Boolean operators only work on integers");}}
    | '(' expr ')' { $$ = $2;   $$->exprType.op = $2->exprType.op;}
    | arrayExpr {$$ = $1;       $$->exprType.op = $1->exprType.op;}
    /* | expr '[' expr ']' %prec ARR{printf("Found array expression\n");} */
    /* | expr INC */
    ;

arrayExpr: expr '[' expr ']' %prec ARR {
        // printf("Found array expression type %d\n", $1->exprType.ndim);
        if($1->exprType.op != T_ARRAY){
            compileError($1->src, $1->src.length + $3->src.length + 2, "Invalid indexing target. Only array types can be indexed.");
        }
        if($3->exprType.op != T_INT){
            compileError($3->src, $3->src.length, "Only int types can be used as indices.");
        }
        $$ = oprNode('[', 2, $1, $3);
        $$->exprType.base = $1->exprType.base;
        $$->exprType.op = $1->exprType.ndim == 1 ? $1->exprType.base : T_ARRAY;
        $$->exprType.ndim = $1->exprType.ndim - 1;
        $$->src.length = $1->src.length + $3->src.length + 2;
    }

callExpr: IDENTIFIER '(' arg_list ')' {
                Symbol* callee = lookup($1.name, identifiers);
                if(!callee){
                    // compileError("Error: Function '%s' not defined", $1);
                    compileError($1.src, strlen($1.name), "Function '%s' not defined", $1.name);
                }
                if(callee->type->op != T_FUNCTION){
                    compileError($1.src, strlen($1.name), "Identifier '%s' is not a function", $1.name);
                }
                
                //Type check all parameters
                Node *param = $3;
                int i=callee->type->size-1;
                // printf("Starting with %d params\n", i);
                //ignore type checking for variadic functions
                if(!callee->type->variadicFunc){
                        // printf("here\n");
                if(param){
                        while(param->as.opr.type==OPR_LIST && i >= 0){
                            // printf("Comparing with original type= %d\n", callee->type->proto[i]->op);
                            if(!typeCheckAssign(callee->type->proto[i]->op, param->as.opr.operands[1]->exprType.op)){
                                compileError(param->as.opr.operands[1]->src, param->as.opr.operands[1]->src.length, "Type mismatch in function call to '%s'", $1.name);
                            }
                            param = param->as.opr.operands[0];
                            i--;
                        }
                        if(i>=0){
                        // printf("Comparing with original type %d \n", /* param->exprType.op, */ callee->type->proto[i]->op);
                        // printf("inside %d\n", callee->type->proto[i] == NULL);
                        }
                        if(i<0 && !callee->type->variadicFunc) {
                                compileError($1.src, strlen($1.name), "Too many parameters in function call to '%s'", $1.name);
                        }
                        if(!callee->type->variadicFunc && !typeCheckAssign(callee->type->proto[i]->op, param->exprType.op)){
                            compileError($1.src, strlen($1.name), "Type mismatch in function call to '%s'", $1.name);
                        }
                        i--;
                    }
                    if(i >= 0){
                        compileError($1.src, strlen($1.name), "Too few parameters in function call to '%s'; expected %d", $1.name, callee->type->size);
                    }
                }
                $$ = oprNode(OPR_CALL, 2, identifierNode(callee), $3);
                $$->exprType.op = callee->type->type->op;
                // printNode($$);
    }

arg_list: expr {$$ = $1;/* oprNode(OPR_LIST, 1,$1); */}
    | arg_list ',' expr {$$ = oprNode(OPR_LIST, 2, $1, $3);}
    | {$$ = NULL;}
    ;

returnStmt: RETURN {
                Coordinate src;
                src.line = lineno;
                src.col = 0;
                compileError(src, 0, "Expected an expression to return");
                $$ = oprNode(OPR_RETURN, 0);
            } 
        | RETURN expr {
            if(!typeCheckAssign(currentFunctionType->type->op, $2->exprType.op)){
                compileError($2->src, $2->src.length, "Type mismatch in return statement");
            }
            $$ = oprNode(OPR_RETURN, 1, $2);
        }
    ;

continueStmt: CONTINUE {$$ = oprNode(OPR_CONTINUE, 0);}
    ; 
breakStmt: BREAK {$$ = oprNode(OPR_BREAK, 0);}
    ;
%%
void typeCheckArrayInitialiser(Type* elementType, Node* expr){
    /* printf("here\n"); */
    Node* exprList = expr;
    TypeEnum baseType = getArrayBaseType(elementType);
    /* printf("Starting array %d\n", elementType->type->op, exprList); */
    /* printNode(exprList);
    printf("\n\n======\n"); */
    if(exprList == NULL) return;
    if(elementType == NULL){
        compileError(exprList->src, exprList->src.length, "Invalid array element type");
    }
    //if it is not a list, this is the last element
    if(exprList->type != NODE_OPR && exprList->as.opr.type != OPR_LIST){
        Node* insideElement = exprList;//->as.opr.operands[0];
        if(elementType->type == NULL){
            compileError( insideElement->src,  insideElement->src.length, "Invalid array element type");
        }
        /* printf("Checking 1) %d %d\n", elementType->type->op, insideElement->exprType.op); */
        if(!typeCheckAssign(elementType->type->op, insideElement->exprType.op) && !typeCheckAssign(baseType, insideElement->exprType.op)){
            compileError( insideElement->src,  insideElement->src.length, "Invalid array element type %d %d", elementType->type->op, insideElement->exprType.op);
        }
        if(insideElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, insideElement);
        }
    } else {
        //this is a list, so check the second operand
        //if it is a list, it will be checked recursively
        /* printf("Checking %d %d\n", elementType->type->op, exprList->as.opr.operands[1]->exprType.op); */
        Node* localElement = exprList->as.opr.operands[1];
        if(localElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, exprList->as.opr.operands[1]);
        }
        TypeEnum baseType = getArrayBaseType(elementType);
        /* printf("Checking 2) %d %d\n", baseType, localElement->exprType.op); */
        if(!typeCheckAssign(baseType, localElement->exprType.op) && !typeCheckAssign(elementType->type->op, localElement->exprType.op)){
            compileError(localElement->src, localElement->src.length, "Invalid array element type 2");
        }
        //advance to next element in list
        typeCheckArrayInitialiser(elementType, exprList->as.opr.operands[0]);
    }
}
void typeCheckUnary(Node* node){
    int invalid = 0;
    switch(node->type){
        case NODE_LITERAL:
            //cannot operate on strings
            invalid = (node->as.value->type == T_ARRAY);
            break;
        case NODE_SYMBOL:
            //cannot operate on arrays
            invalid = (node->as.symbol->type->op == T_ARRAY);
            break;
        case NODE_OPR:
            //cannot operate on arrays
            invalid = (node->exprType.op == T_ARRAY);
            break;
        default:
            invalid = 1;
            break;
    }
    if(invalid){
        Coordinate src;
        src.line=lineno;
        src.col = col;
        compileError(src, 1, "Invalid operand type");
    }
}
/* Type check two types
   Tries to widen a type to match the other,
   otherwise raises compileError.
 */
int typeCheckAssign(TypeEnum varType, TypeEnum exprType){
    //exprType cannot larger than varType
    if(varType != T_ARRAY && exprType == T_ARRAY){
        return 0;
    }
    if(varType == T_ARRAY && exprType != T_ARRAY){
        return 0;
    }
    if(varType == T_FUNCTION && exprType != T_FUNCTION){
        return 0;
    }
    if(varType == T_FLOAT){
        if(exprType == T_FUNCTION || exprType == T_ARRAY){
            return 0;
        }
        return 1;
    }

    return varType == exprType;
}

void point_at_in_line(int lineno, int from, int to);

Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...){
    Symbol* foundIdentifier = lookup(name, table);
    if(!foundIdentifier){
        va_list args;
        va_start(args, format);
        fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] ", currentFileName, src.line, src.col);
        fprintf(stderr, "Error: " ANSI_COLOR_RESET);
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        point_at_in_line(src.line-1, src.col -1 , src.col + strlen(name) -1 );
        va_end(args);
        exit(1);
    }
    return foundIdentifier;
}

/**
    * Prints a message to stderr and exits the program
    * @param format The format string
    * @param ... The arguments to the format string
*/
void compileError(Coordinate src, int lexemeLength, char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] ", currentFileName, src.line, src.col);
    fprintf(stderr, ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    point_at_in_line(src.line-1, src.col -1 , src.col + lexemeLength -1 );
    va_end(args);
    exit(1);
}
// Prints the error but does not exit.
void errorMessage(Coordinate src, int lexemeLength, char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    point_at_in_line(src.line-1, src.col -1 , src.col + lexemeLength -1 );
    va_end(args);
}
/* int main(int argc, char* argv[]){
    return 0;
} */
/* int yyerror(char *s){
  exit(1);
  return 1;
} */