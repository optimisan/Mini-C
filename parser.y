%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "./util/AST.h"
#include "./util/symbol.h"
#include "./util/token.h"

char *currentFileName;
extern int level;
extern int lineno, col;

int yyerror(char *s);
Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...);
void compileError(Coordinate pos, int lexemeLength, char *format, ...);
int typeCheckAssign(TypeEnum t1, TypeEnum t2);
TypeEnum typeWiden(TypeEnum t1, TypeEnum t2);
void typeCheckUnary(Node* t);
void typeCheckArrayInitialiser(Type* elementType, Node* expr);
int yylex();
%}

%union {
    int iValue;
    float fValue;
    char* sValue;
    IdStruct id;
    char cValue;
    int* sizes;
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
%left '*' '/'
/* Math op */
%token INC DEC
%nonassoc UMINUS
%left '[' ']'
%nonassoc ARR

%type <node> expr arrayExpr callExpr arg_list continueStmt breakStmt returnStmt varInitialiser varNames arraySpecifier varDeclaration arrayInitialiser array_init_list param_list functionDecl declarations declaration funcBody stmtOrDecl stmt assignExpr switchStmt switchBody switches cases caseLabel caseType whileStmt blockStmt ifStmt forStmt forInit forCond forIter
%type <iValue> varType
/* %t declarations declaration functionDecl param_list varInitialiser varDeclaration varType varNames arraySpecifier funcBody stmtOrDecl stmt assignExpr switchStmt switchBody switches cases caseLabel caseType whileStmt blockStmt ifStmt expr arrayExpr callExpr returnStmt continueStmt breakStmt arg_list */

%%

program: declarations EOF_TOKEN {printf("Program end\n"); return 0;}
    ;

declarations: declarations declaration { $$ = oprNode(OPR_LIST, 2, $1, $2); }
    |
    ;

declaration: functionDecl
    | functionDecl ';'
    | varDeclaration ';'
    ;

functionDecl: varType IDENTIFIER '(' param_list ')' 
                        {
                            Symbol* funcSymbol = install($2.name, &identifiers, level, $2.src);
                            if(funcSymbol->type){
                                compileError($2.src, strlen($2.name), "Function %s already declared", $2.name);
                            }
                            Type* funcType = malloc(sizeof(Type));
                            funcSymbol->type = funcType;
                            funcType->sym = funcSymbol;
                            funcType->op = T_FUNCTION;
                            funcType->type = malloc(sizeof(Type));
                            funcType->type->op = $1;
                            int numParams=0;
                            Node* temp = $4;
                            while(temp){
                                numParams++;
                                if(temp->as.opr.nops == 3)
                                    temp = temp->as.opr.operands[1];
                                else temp = NULL;
                            }
                            funcType->size = numParams;
                            funcType->proto = malloc(sizeof(Type*) * numParams);
                            Node* param = $4;
                            int i=0;
                            while(param){
                                if(param->as.opr.nops == 2){
                                    //last param
                                    // printf("Type of param is %d\n", param->as.opr.operands[0]->type);
                                    funcType->proto[i] = param->as.opr.operands[1]->as.symbol->type;
                                } else {
                                    funcType->proto[i] = param->as.opr.operands[2]->as.symbol->type;
                                }
                                i++;
                                if(param->as.opr.nops == 3)
                                    param = param->as.opr.operands[1];
                                else param = NULL;
                            }
                            beginScope();
                        }
            funcBody
                {
                    endScope();
                }

param_list: varType IDENTIFIER {
                        Symbol* psym = install($2.name, &identifiers, level, $2.src);
                        $$ = oprNode(OPR_LIST, 2, $1, identifierNode(psym)); 
                        printf("Found param %s\n", $2.name);
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = $1;
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                    }
    | param_list ',' varType IDENTIFIER {
                        printf("Found param %s\n", $4.name);
                        Symbol* psym = install($4.name, &identifiers, level, $4.src);
                        if(psym->type){
                            compileError($4.src, strlen($4.name), "Parameter %s already declared", $4.name);
                        }
                        $$ = oprNode(OPR_LIST, 3, $1, identifierNode(psym), $3);
                    }
    | {$$=NULL;}
    ;

varInitialiser: IDENTIFIER arraySpecifier {
                                    $$ = oprNode('=', 2, identifierNode(install($1.name, &identifiers, level, $1.src)), $2);
                                    printf("var init");
                                    }
    | IDENTIFIER arraySpecifier '=' expr {
                                    $$ = oprNode('=', 3, identifierNode(install($1.name, &identifiers, level, $1.src)), $2, $4);
                                    }
    | IDENTIFIER arraySpecifier '=' arrayInitialiser {$$ = oprNode('=', 3, identifierNode(install($1.name, &identifiers, level, $1.src)), $2, $4);}

arrayInitialiser: '{' array_init_list '}' { $$ = $2; $$->exprType.op = T_ARRAY;}

array_init_list: expr { $$ = oprNode(OPR_LIST, 1, $1);}
    | array_init_list ',' expr { $$ = oprNode(OPR_LIST, 3, $1, $3, NULL); }
    | arrayInitialiser { $$ = oprNode(OPR_LIST, 1, $1); $$->exprType.op = T_ARRAY;}
    | array_init_list ',' arrayInitialiser { $$ = oprNode(OPR_LIST, 3, $1, $3, NULL); $$->exprType.op = T_ARRAY;}
    ;

/* expr_list: expr
    | expr_list ',' expr
    |
    ; */

varDeclaration: varType varNames {
    $$ = oprNode(OPR_VAR_DECL, 1, $2);
    printf("Found var decl %d, \n", $2->as.opr.type);
    //iterate through the list of variables and add them to the symbol table
    Node* varName = $2;
    while(varName != NULL) {
        Node* varInitialiser;
        if(varName->as.opr.type == OPR_LIST) {
            varInitialiser = varName->as.opr.operands[1];
            printf("Found list %d\n", varInitialiser->as.opr.type);
        } else {
            varInitialiser = varName;
        }
        printf("Found var decl for '%s', \n", varInitialiser->as.opr.operands[0]->as.symbol->name);
        Symbol* varSymbol = varInitialiser->as.opr.operands[0]->as.symbol;
        Symbol* installed = install(varSymbol->name, &identifiers, level, varSymbol->src);
        Coordinate src = varSymbol->src;
        if(installed->type){
            compileError(varSymbol->src, strlen(varSymbol->name), "Variable %s already declared", varSymbol->name);
        }
        Type* type = malloc(sizeof(Type));
        type->sym = installed;
        installed->type = type;
        type->op = $1;
        int arrLastSize = -1;
        //check if this is an array
        if(varInitialiser->as.opr.operands[1] != NULL){
            Node* arraySpecifier = varInitialiser->as.opr.operands[1];
            Type* innerType = type;
            do {
                arrLastSize = arraySpecifier->as.opr.operands[1]->as.value->as.integer;
                //check if size is declared for dimensions other than first
                if(arrLastSize <= 0 && arraySpecifier->as.opr.operands[0] != NULL){
                    compileError(src, strlen(varSymbol->name), "Array dimensions except the first cannot be empty %d", arrLastSize);
                }
                Type* outerType = malloc(sizeof(Type));
                outerType->sym = installed;
                outerType->op = T_ARRAY;
                outerType->type = innerType;
                outerType->size = arrLastSize;
                innerType = outerType;
            } while((arraySpecifier = arraySpecifier->as.opr.operands[0]));
            installed->type=innerType;
        }

        // printf("\nType op of this var is %d\n", installed->type->op);
        
        //Check if there is an initialiser expression assignment
        if(varInitialiser->as.opr.nops == 3){
            Node* expr = varInitialiser->as.opr.operands[2];
            // printf("Found initialiser %d\n", expr->exprType);
            if(!typeCheckAssign(installed->type->op, expr->exprType.op)){
                compileError(src, strlen(varSymbol->name), "Type mismatch in variable initialisation %s", varSymbol->name);
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

funcBody: '{' {beginScope();}
            stmtOrDecl
          '}' {endScope();}

stmtOrDecl: stmtOrDecl stmt
    | stmtOrDecl varDeclaration ';'
    | 
    ;


/* stmtList: stmtList stmt
    |
    ; */

stmt: ';'
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

}

forInit: assignExpr
    | varDeclaration
    | 
    ;

forCond: expr
    | 
    ;

forIter: assignExpr
    | {$$=NULL;}
    ;

assignExpr: IDENTIFIER '=' expr {
                printf("Found assign target\n");
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                if(!typeCheckAssign(sym->type->op, $3->exprType.op)){
                    compileError($1.src, strlen($1.name), "Type mismatch in assignment %s", $1.name);
                }
                $$ = oprNode(OPR_ASSIGN, 2, identifierNode(sym), $3);
            }
    | IDENTIFIER INC {
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError($1.src, strlen($1.name), "Only int and float can be incremented %s", $1.name);
                }
                $$ = oprNode(OPR_INC, 1, identifierNode(sym));
            }
    | IDENTIFIER DEC {
                Symbol* sym = getSymbol($1.name, identifiers, $1.src, "Variable '%s' not declared", $1.name);
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError($1.src, strlen($1.name), "Only int and float can be decremented %s", $1.name);
                }
                $$ = oprNode(OPR_DEC, 1, identifierNode(sym));
            }
    | arrayExpr '=' expr {
                printf("Got array type as %d\n", $1->exprType.op);
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

switchStmt: SWITCH '(' expr ')' switchBody

switchBody: '{' switches '}'

switches: cases 
    |
    ;

cases: caseLabel 
    | caseLabel stmt
    | cases caseLabel 
    | cases caseLabel stmt
    ;

caseLabel: caseType expr ':' ;

caseType: CASE | DEFAULT ;

whileStmt: WHILE '(' expr ')' stmt

blockStmt: '{'          {beginScope();}
            stmtOrDecl 
           '}'
                        {endScope();}
            ;

ifStmt: IF '(' expr ')' stmt %prec IFX {printf("Unmatched if statement\n");}
    | IF '(' expr ')' stmt ELSE stmt {printf("Matched if statement\n");}

expr: INTEGER {$$ = intNode($1);}
    | CHARACTER {$$ = charNode($1); }
    | IDENTIFIER { 
            Symbol* foundId = getSymbol($1.name, identifiers, $1.src, "Identifier '%s' not declared in this scope", $1.name);
            $$ = identifierNode(foundId);
            printf("Idenfitier base type is %d\n", $$->exprType.ndim);
        }
    | FLOAT {$$ = floatNode($1);}
    | STRING {$$ = strNode($1, strlen($1)); printf("String here, %d\n", $$->src.length);}
    | callExpr {$$ = $1;}
    | '-' expr %prec UMINUS { $$ = oprNode('-', 1, $2); typeCheckUnary($2); $$->exprType.op = $2->exprType.op;}
    | '!' expr %prec UMINUS { $$ = oprNode('!', 1, $2); typeCheckUnary($2); $$->exprType.op = $2->exprType.op;}
    | expr '+' expr { $$ = oprNode('+', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '-' expr { $$ = oprNode('-', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '*' expr { $$ = oprNode('*', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '/' expr { $$ = oprNode('/', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '<' expr { $$ = oprNode('<', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr '>' expr { $$ = oprNode('>', 2, $1, $3);     $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr GE expr { $$ = oprNode(OPR_GE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr LE expr { $$ = oprNode(OPR_LE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr EQ expr { $$ = oprNode(OPR_EQ, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr NE expr { $$ = oprNode(OPR_NE, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr AND expr { $$ = oprNode(OPR_AND, 2, $1, $3); $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | expr OR expr { $$ = oprNode(OPR_OR, 2, $1, $3);   $$->exprType.op = typeWiden($1->exprType.op, $3->exprType.op);}
    | '(' expr ')' { $$ = $2;   $$->exprType.op = $2->exprType.op;}
    | arrayExpr {$$ = $1;       $$->exprType.op = $1->exprType.op;}
    /* | expr '[' expr ']' %prec ARR{printf("Found array expression\n");} */
    /* | expr INC */
    ;

arrayExpr: expr '[' expr ']' %prec ARR {
        printf("Found array expression type %d\n", $1->exprType.ndim);
        if($1->exprType.op != T_ARRAY){
            compileError($1->src, $1->src.length + $3->src.length + 2, "Invalid indexing target. Only array types can be indexed.");
        }
        if($3->exprType.op != T_INT){
            compileError($3->src, $3->src.length, "Only int types can be used as indices.");
        }
        $$ = oprNode(OPR_ARRAY_INDEX, 2, $1, $3);
        $$->exprType.op = $1->exprType.ndim == 1 ? $1->exprType.base : T_ARRAY;
        $$->exprType.ndim = $1->exprType.ndim - 1;
        // $$->exprType.op = $1->exprType.op->type;
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
                printf("Starting with %d params\n", i);
                if(param){
                    printf("here\n");
                    while(param->as.opr.nops==2 && i >= 0){
                        printf("Comparing with original type %d\n", param->as.opr.operands[1]->exprType.op);
                        if(!typeCheckAssign(callee->type->proto[i]->op, param->as.opr.operands[1]->exprType.op)){
                            compileError(param->as.opr.operands[1]->src, param->as.opr.operands[1]->src.length, "Type mismatch in function call to '%s'", $1.name);
                        }
                        param = param->as.opr.operands[0];
                        i--;
                    }
                    printf("Comparing with original type %d %d\n", param->exprType.op, i);
                    if(i<0) {
                            compileError($1.src, strlen($1.name), "Too many parameters in function call to '%s'", $1.name);
                    }
                    if(!typeCheckAssign(callee->type->proto[i]->op, param->exprType.op)){
                        compileError($1.src, strlen($1.name), "Type mismatch in function call to '%s'", $1.name);
                    }
                    i--;
                }
                if(i >= 0){
                    compileError($1.src, strlen($1.name), "Too few parameters in function call to '%s'; expected %d", $1.name, callee->type->size);
                }
                $$ = oprNode(OPR_CALL, 2, identifierNode(callee), $3);
                $$->exprType.op = callee->type->type->op;
                printNode($$);
    }

arg_list: expr {$$ = oprNode(OPR_LIST, 1,$1);}
    | arg_list ',' expr {$$ = oprNode(OPR_LIST, 2, $1, $3);}
    | {$$ = NULL;}
    ;

returnStmt: RETURN 
    | RETURN expr
    ;

continueStmt: CONTINUE {$$ = oprNode(OPR_CONTINUE, 0);}
    ; 
breakStmt: BREAK {$$ = oprNode(OPR_BREAK, 0);}
    ;
%%
void typeCheckArrayInitialiser(Type* elementType, Node* expr){
    Node* exprList = expr;
    /* printf("Starting array %d\n", elementType->type->op, exprList); */
    if(exprList == NULL) return;
    //if it is not a list, this is the last element
    if(exprList->as.opr.nops == 1){
        Node* insideElement = exprList->as.opr.operands[0];
        printf("Checking 1) %d %d\n", elementType->type->op, insideElement->exprType.op);
        if(!typeCheckAssign(elementType->type->op, insideElement->exprType.op)){
            compileError( insideElement->src,  insideElement->src.length, "Invalid array element type");
        }
        if(insideElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, insideElement);
        }
    } else {
        //this is a list, so check the second operand
        //if it is a list, it will be checked recursively
        /* printf("Checking %d %d\n", elementType->type->op, exprList->as.opr.operands[1]->exprType.op); */
        Node* localElement = exprList->as.opr.operands[1];
        if(localElement->exprType.op != elementType->type->op){
            compileError(localElement->src, localElement->src.length, "Invalid array element type 2");
        }
        if(localElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, exprList->as.opr.operands[1]);
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

    if(exprType == T_FLOAT && varType != T_FLOAT){
        return 0;
    }
    return 1;
}

TypeEnum typeWiden(TypeEnum t1, TypeEnum t2){
    //arrays are not allowed
    if(t1 == T_ARRAY || t2 == T_ARRAY){
        return -1;
    }
    if(t1 == T_FLOAT || t2 == T_FLOAT){
        return T_FLOAT;
    }
    if(t1 == T_INT || t2 == T_INT){
        return T_INT;
    }
    if(t1 == T_CHAR || t2 == T_CHAR){
        return T_CHAR;
    }
    return -1;
}


void point_at_in_line(int lineno, int from, int to);

Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...){
    Symbol* foundIdentifier = lookup(name, table);
    if(!foundIdentifier){
        va_list args;
        va_start(args, format);
        fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
        fprintf(stderr, "Error: ");
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
    fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    point_at_in_line(src.line-1, src.col -1 , src.col + lexemeLength -1 );
    va_end(args);
    exit(1);
}
/* int main(int argc, char* argv[]){
    return 0;
} */
/* int yyerror(char *s){
  exit(1);
  return 1;
} */