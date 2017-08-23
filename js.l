%{
#include <stdio.h>
#include <string.h>
#include "js.h"
#include "y.tab.h"
#include "util.h"
#include "create.h"
#include "error.h"
#include "message.h"
int
yywrap(void)
{
    return 1;
}

%}
%start COMMENT STRING_LITERAL_STATE
%%
<INITIAL>"function"     return FUNCTION;
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>else[ ]*if        return ELSIF;
<INITIAL>"while"        return WHILE;
<INITIAL>"for"          return FOR;
<INITIAL>"return"       return RETURN_T;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"null"         return NULL_T;
<INITIAL>"true"         return TRUE_T;
<INITIAL>"false"        return FALSE_T;
<INITIAL>"("            return LP;
<INITIAL>")"            return RP;
<INITIAL>"{"            return LC;
<INITIAL>"}"            return RC;
<INITIAL>"["            return LB;
<INITIAL>"]"            return RB;
<INITIAL>";"            return SEMICOLON;
<INITIAL>","            return COMMA;
<INITIAL>"&&"           return LOGICAL_AND;
<INITIAL>"||"           return LOGICAL_OR;
<INITIAL>"="            return ASSIGN;
<INITIAL>"=="           return EQ;
<INITIAL>"!="           return NE;
<INITIAL>">"            return GT;
<INITIAL>">="           return GE;
<INITIAL>"<"            return LT;
<INITIAL>"<="           return LE;
<INITIAL>"+"            return ADD;
<INITIAL>"-"            return SUB;
<INITIAL>"*"            return MUL;
<INITIAL>"/"            return DIV;
<INITIAL>"%"            return MOD;
<INITIAL>"++"           return INCREMENT;
<INITIAL>"--"           return DECREMENT;
<INITIAL>"."            return DOT;
<INITIAL>"var"          return VAR;
<INITIAL>"new"          return NEW;
<INITIAL>":"            return COLON;
<INITIAL>"in"            return IN;
<INITIAL>"+="            return PLUS_ASSIGN;
<INITIAL>"-="            return MINUS_ASSIGN;
<INITIAL>"*="            return MUL_ASSIGN;
<INITIAL>"/="            return DIV_ASSIGN;
<INITIAL>"%="            return MOD_ASSIGN;
<INITIAL>"typeof"            return TYPEOF;

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    yylval.identifier = CREATE_identifier(yytext);
    return IDENTIFIER;
}
<INITIAL>([1-9][0-9]*)|"0" {
    Expression  *expression = CREATE_alloc_expression(EXPRESSION_TYPE_INT);
    sscanf(yytext, "%d", &expression->u.int_value);
    yylval.expression = expression;
    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    Expression  *expression = CREATE_alloc_expression(EXPRESSION_TYPE_FLOAT);
    sscanf(yytext, "%lf", &expression->u.double_value);
    yylval.expression = expression;
    return DOUBLE_LITERAL;
}
<INITIAL>\" {
    alloc_temprory_string();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>[ \t] ;
<INITIAL>\n {
    increment_line_number();
}
<INITIAL>\/\/     BEGIN COMMENT;
<INITIAL>.      {
    char buf[LINE_BUF_SIZE];

    if (isprint(yytext[0])) {
        buf[0] = yytext[0];
        buf[1] = '\0';
    } else {
        sprintf(buf, "0x%02x", (unsigned char)yytext[0]);
    }

    ERROR_compile_error(CHARACTER_INVALID_ERR, buf);
}
<COMMENT>\n     {
    increment_line_number();
    BEGIN INITIAL;
}
<COMMENT>.      ;
<STRING_LITERAL_STATE>\"        {
    Expression *expression = CREATE_alloc_expression(EXPRESSION_TYPE_STRING);
    appendchar_temprory_string('\0');
    expression->u.string = literal_string_holder->s;
    yylval.expression = expression;
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\n        {
    appendchar_temprory_string('\n');
    increment_line_number();
}
<STRING_LITERAL_STATE>\\\"      appendchar_temprory_string('"');
<STRING_LITERAL_STATE>\\n       appendchar_temprory_string('\n');
<STRING_LITERAL_STATE>\\t       appendchar_temprory_string('\t');
<STRING_LITERAL_STATE>\\\\      appendchar_temprory_string('\\');
<STRING_LITERAL_STATE>.         appendchar_temprory_string(yytext[0]);
%%
