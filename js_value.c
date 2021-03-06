#include "js.h"
#include "js_value.h"
#include <string.h>
#include <stdarg.h>
#include "interprete.h"
#include "error.h"
#include <stdlib.h>

JSBool is_js_value_true(const JsValue *v)
{
	if (JS_VALUE_TYPE_BOOL == v->typ)
	{
		return v->u.boolvalue;
	}
	if (JS_VALUE_TYPE_INT == v->typ)
	{
		if (0 != v->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v->typ)
	{
		if (v->u.floatvalue < SMALL_FLOAT && v->u.floatvalue > -SMALL_FLOAT)
		{
			return JS_BOOL_FALSE;
		}
		else
		{
			return JS_BOOL_TRUE;
		}
	}
	if (JS_VALUE_TYPE_STRING == v->typ)
	{
		int length = v->u.string->length;
		if (0 == length)
		{
			return JS_BOOL_FALSE;
		}
		else
		{
			return JS_BOOL_TRUE;
		}
	}
	if (JS_VALUE_TYPE_ARRAY == v->typ)
	{
		if (0 == v->u.array->length)
		{
			return JS_BOOL_FALSE;
		}
		else
		{
			return JS_BOOL_TRUE;
		}
	}
	if (JS_VALUE_TYPE_OBJECT == v->typ)
	{
		return JS_BOOL_TRUE;
	}
	if (JS_VALUE_TYPE_STRING_LITERAL == v->typ)
	{
		if (0 == strlen(v->u.literal_string))
		{
			return JS_BOOL_FALSE;
		}
		else
		{
			return JS_BOOL_TRUE;
		}
	}
	return JS_BOOL_FALSE;
}

JSBool js_reverse_bool(JSBool b)
{
	if (JS_BOOL_TRUE == b)
	{
		return JS_BOOL_FALSE;
	}
	else
	{
		return JS_BOOL_TRUE;
	}
}

JsValue js_increment_or_decrement(const JsValue *v, char increment)
{
	JsValue ret = *v;
	if (JS_VALUE_TYPE_INT == v->typ)
	{
		if (1 == increment)
		{
			ret.u.intvalue++;
		}
		else
		{
			ret.u.intvalue--;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v->typ)
	{
		if (1 == increment)
		{
			ret.u.floatvalue++;
		}
		else
		{
			ret.u.floatvalue--;
		}
	}
	if (JS_VALUE_TYPE_BOOL == v->typ)
	{
		ret.u.boolvalue = js_reverse_bool(v->u.boolvalue);
	}
	return ret;
}

JsValue js_negative(const JsValue *const v)
{
	JsValue ret = *v;
	if (JS_VALUE_TYPE_INT == v->typ)
	{
		ret.u.intvalue -= 2 * v->u.intvalue;
	}
	if (JS_VALUE_TYPE_FLOAT == v->typ)
	{
		ret.u.floatvalue -= 2 * v->u.floatvalue;
	}
	if (JS_VALUE_TYPE_BOOL == v->typ)
	{
		ret.u.boolvalue = js_reverse_bool(v->u.boolvalue);
	}
	return ret;
}



JsValue js_value_add(JsInterpreter *inter, const JsValue *const v1, const JsValue *const v2, int line)
{
	JsValue v = *v1;
	/*handle bool part*/
	if (JS_VALUE_TYPE_BOOL == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v2->u.intvalue + v1->u.boolvalue;
		return v;
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_BOOL == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue + v2->u.boolvalue;
		return v;
	}

	/*handle number part*/
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue + v2->u.intvalue;
		return v;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.intvalue;
		return v;
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue + v2->u.floatvalue;
		return v;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = EXPRESSION_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue + v2->u.floatvalue;
		return v;
	}

	/*handle string part*/
	if (JS_VALUE_TYPE_STRING == v1->typ || JS_VALUE_TYPE_STRING_LITERAL == v1->typ)
	{
		JsValue vv2 = js_to_string(inter, v2, line);
		return INTERPRETER_concat_string(inter, v1, &vv2, line);
	}

	if (JS_VALUE_TYPE_STRING == v2->typ || JS_VALUE_TYPE_STRING_LITERAL == v2->typ)
	{
		JsValue vv1 = js_to_string(inter, v1, line);
		return INTERPRETER_concat_string(inter, &vv1, v2, line);
	}

	return v;
}

JsValue js_to_string(JsInterpreter *inter, const JsValue *value, int line)
{
	JsValue v;
	v.typ = JS_VALUE_TYPE_STRING;
	Heap *h;
	switch (value->typ)
	{
	case JS_VALUE_TYPE_BOOL:
		if (JS_BOOL_TRUE == value->u.boolvalue)
		{
			v.u.literal_string = "true";
		}
		else
		{
			v.u.literal_string = "false";
		}
		break;
	case JS_VALUE_TYPE_INT: /*how to calculate size */
		v.u.string = INTERPRETER_create_heap(inter, JS_VALUE_TYPE_STRING, 100, line);
		v.u.string->length = snprintf(v.u.string->s, 100, "%d", value->u.intvalue);
		break;
	case JS_VALUE_TYPE_FLOAT:
		v.u.string = INTERPRETER_create_heap(inter, JS_VALUE_TYPE_STRING, 100, line);
		v.u.string->length = snprintf(v.u.string->s, 100, "%f", value->u.floatvalue);
		break;
	case JS_VALUE_TYPE_STRING:
		v = *value;
		break;
	case JS_VALUE_TYPE_ARRAY:
		v.typ = JS_VALUE_TYPE_STRING_LITERAL;
		v.u.literal_string = "array";
		break;
	case JS_VALUE_TYPE_FUNCTION:
		v.typ = JS_VALUE_TYPE_STRING_LITERAL;
		v.u.literal_string = "function";
		break;
	case JS_VALUE_TYPE_NULL:
		v.typ = JS_VALUE_TYPE_STRING_LITERAL;
		v.u.literal_string = "null";
		break;
	case JS_VALUE_TYPE_UNDEFINED:
		v.typ = JS_VALUE_TYPE_STRING_LITERAL;
		v.u.literal_string = "undefined";
		break;
	case JS_VALUE_TYPE_STRING_LITERAL:
		v = *value;
		break;
	case JS_VALUE_TYPE_OBJECT:
		v.typ = JS_VALUE_TYPE_STRING_LITERAL;
		v.u.literal_string = "object";
		break;
	}
	return v;
}

JsValue js_value_mod(const JsValue *v1, const JsValue *v2)
{
	JsValue v;
	v.typ = JS_VALUE_TYPE_INT;
	int left = 0;
	int right = 0;
	if (JS_VALUE_TYPE_INT == v1->typ)
	{
		left = v1->u.intvalue;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ)
	{
		left = (int)v1->u.floatvalue;
	}
	if (JS_VALUE_TYPE_INT == v2->typ)
	{
		right = v2->u.intvalue;
	}
	if (JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		right = (int)v2->u.floatvalue;
	}
	if (0 == left || 0 == right)
	{
		v.u.intvalue = 0;
	}
	else
	{
		v.u.intvalue = left % right;
	}
	return v;
}

JsValue js_value_mul(const JsValue *v1, const JsValue *v2)
{
	JsValue v;
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue * v2->u.intvalue;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue * v2->u.intvalue;
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue * v2->u.floatvalue;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue * v2->u.floatvalue;
	}
	return v;
}

JsValue js_value_div(const JsValue *v1, const JsValue *v2)
{
	JsValue v;
	v.typ = JS_VALUE_TYPE_FLOAT;
	v.u.floatvalue = 0;
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (0 != v2->u.intvalue)
		{
			v.u.floatvalue = ((double)v1->u.intvalue) / ((double)v2->u.intvalue);
		}
		else
		{
			v.typ = JS_VALUE_TYPE_INT;
			v.u.intvalue = MAX_INT;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (0 != v2->u.intvalue)
		{
			v.u.floatvalue = v1->u.floatvalue / ((double)v2->u.intvalue);
		}
		else
		{
			v.u.floatvalue = MAX_INT;
		}
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		if (!IS_ZOER(v2->u.floatvalue))
		{
			v.u.floatvalue = ((double)v1->u.intvalue) / v2->u.floatvalue;
		}
		else
		{
			v.u.floatvalue = MAX_INT;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue / v2->u.floatvalue;
	}
	return v;
}

double js_parse_string(char *str)
{
	return atof(str);
}

double js_value_to_double(const JsValue *v)
{
	double d = MAX_INT;
	switch (v->typ)
	{
	case JS_VALUE_TYPE_BOOL:
		if (JS_BOOL_TRUE == v->u.boolvalue)
		{
			d = 1.0;
		}
		else
		{
			d = 0.0;
		}
		break;
	case JS_VALUE_TYPE_INT:
		d = v->u.intvalue;
		break;
	case JS_VALUE_TYPE_FLOAT:
		d = v->u.floatvalue;
		break;
	case JS_VALUE_TYPE_ARRAY:
		d = 1.0;
		break;
	case JS_VALUE_TYPE_NULL:
		d = 0.0;
		break;
	case JS_VALUE_TYPE_UNDEFINED:
		d = 0.0;
		break;
	case JS_VALUE_TYPE_OBJECT:
		d = 1.0;
		break;
	case JS_VALUE_TYPE_STRING_LITERAL:
		d = js_parse_string(v->u.literal_string);
		break;
	case JS_VALUE_TYPE_STRING:
		d = js_parse_string(v->u.string->s);
		break;
	}
	return d;
}

JsValue js_value_sub(const JsValue *v1, const JsValue *v2)
{
	JsValue v = *v1;
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_INT;
		v.u.intvalue = v1->u.intvalue - v2->u.intvalue;
		return v;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue - v2->u.intvalue;
		return v;
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.intvalue - v2->u.floatvalue;
		return v;
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		v.typ = JS_VALUE_TYPE_FLOAT;
		v.u.floatvalue = v1->u.floatvalue - v2->u.floatvalue;
		return v;
	}

	/* see all data as double*/
	v.typ = JS_VALUE_TYPE_FLOAT;
	v.u.floatvalue = js_value_to_double(v1) - js_value_to_double(v2);

	return v;
}

JSBool js_value_equal_string(const JsValue *v1, const JsValue *v2)
{
	char *first;
	char *second;
	if (JS_VALUE_TYPE_STRING == v1->typ)
	{
		first = v1->u.string->s;
	}
	else
	{
		first = v1->u.literal_string;
	}
	if (JS_VALUE_TYPE_STRING == v2->typ)
	{
		second = v2->u.string->s;
	}
	else
	{
		second = v2->u.literal_string;
	}
	if (0 == strcmp(first, second))
	{
		return JS_BOOL_TRUE;
	}
	else
	{
		return JS_BOOL_FALSE;
	}
}

JSBool js_value_equal(const JsValue *v1, const JsValue *v2)
{
	if (
		(JS_VALUE_TYPE_STRING == v1->typ || JS_VALUE_TYPE_STRING_LITERAL == v1->typ) && (JS_VALUE_TYPE_STRING == v2->typ || JS_VALUE_TYPE_STRING_LITERAL == v2->typ))
	{
		return js_value_equal_string(v1, v2);
	}
	if (v1->typ != v2->typ)
	{
		return JS_BOOL_FALSE;
	}
	switch (v1->typ)
	{
	case JS_VALUE_TYPE_BOOL:
		if (v1->u.boolvalue == v2->u.boolvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	case JS_VALUE_TYPE_INT:
		if (v1->u.intvalue == v2->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	case JS_VALUE_TYPE_FLOAT:
		if (v1->u.floatvalue == v2->u.floatvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	case JS_VALUE_TYPE_ARRAY:
		if (v1->u.array == v2->u.array)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	case JS_VALUE_TYPE_OBJECT:
		if (v1->u.object == v2->u.object)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	default:
		return JS_BOOL_FALSE;
	}
}

JSBool js_value_greater_string(const JsValue *v1, const JsValue *v2)
{
	char *first;
	char *second;
	if (JS_VALUE_TYPE_STRING == v1->typ)
	{
		first = v1->u.string->s;
	}
	else
	{
		first = v1->u.literal_string;
	}
	if (JS_VALUE_TYPE_STRING == v2->typ)
	{
		second = v2->u.string->s;
	}
	else
	{
		second = v2->u.literal_string;
	}
	if (strcmp(first, second) > 0)
	{
		return JS_BOOL_TRUE;
	}
	else
	{
		return JS_BOOL_FALSE;
	}
}

JSBool js_value_greater(const JsValue *v1, const JsValue *v2)
{
	if (
		(JS_VALUE_TYPE_STRING == v1->typ || JS_VALUE_TYPE_STRING_LITERAL == v1->typ) && (JS_VALUE_TYPE_STRING == v2->typ || JS_VALUE_TYPE_STRING_LITERAL == v2->typ))
	{
		return js_value_greater_string(v1, v2);
	}

	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (v1->u.intvalue > v2->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		if (v1->u.intvalue > v2->u.floatvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (v1->u.floatvalue > v2->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		if (v1->u.floatvalue > v2->u.floatvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	return JS_BOOL_FALSE;
}

JSBool js_value_greater_string_or_equal(const JsValue *v1, const JsValue *v2)
{

	return JS_BOOL_FALSE;
}

JSBool js_value_greater_or_equal(const JsValue *v1, const JsValue *v2)
{
	if (
		(JS_VALUE_TYPE_STRING == v1->typ || JS_VALUE_TYPE_STRING_LITERAL == v1->typ) &&
		(JS_VALUE_TYPE_STRING == v2->typ || JS_VALUE_TYPE_STRING_LITERAL == v2->typ))
	{
		return js_value_greater_string_or_equal(v1, v2);
	}
	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (v1->u.intvalue >= v2->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	if (JS_VALUE_TYPE_INT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		if (v1->u.intvalue >= v2->u.floatvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}
	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_INT == v2->typ)
	{
		if (v1->u.floatvalue >= v2->u.intvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	if (JS_VALUE_TYPE_FLOAT == v1->typ && JS_VALUE_TYPE_FLOAT == v2->typ)
	{
		if (v1->u.floatvalue >= v2->u.floatvalue)
		{
			return JS_BOOL_TRUE;
		}
		else
		{
			return JS_BOOL_FALSE;
		}
	}

	return JS_BOOL_FALSE;
}

void js_print_object(JsObject *object)
{
	printf("object:{");
	JsKvList *eles = object->eles;
	while (NULL != eles)
	{
		printf("%s:", eles->kv.key);
		js_print(&eles->kv.value);
		printf(" ");
		eles = eles->next;
	}
	printf("}");
}

JsValue js_print(const JsValue *value)
{
	JsValue v = *value;
	switch (value->typ)
	{
	case JS_VALUE_TYPE_BOOL:
		if (JS_BOOL_TRUE == value->u.boolvalue)
		{
			printf("true");
		}
		else
		{
			printf("false");
		}
		break;
	case JS_VALUE_TYPE_INT:
		printf("%d", value->u.intvalue);
		break;
	case JS_VALUE_TYPE_FLOAT:
		printf("%f", value->u.floatvalue);
		break;
	case JS_VALUE_TYPE_STRING:
		printf("%s", value->u.string->s);
		break;
	case JS_VALUE_TYPE_NULL:
		printf("null");
		break;
	case JS_VALUE_TYPE_UNDEFINED:
		printf("undefined");
		break;
	case JS_VALUE_TYPE_ARRAY:
		js_print_array(value->u.array);
		break;
	case JS_VALUE_TYPE_FUNCTION:
		if (NULL == value->u.func->name)
		{
			printf("function");
		}
		else
		{
			printf("function:%s", value->u.func->name);
		}
		break;
	case JS_VALUE_TYPE_OBJECT:
		js_print_object(value->u.object);
		break;
	case JS_VALUE_TYPE_STRING_LITERAL:
		printf("%s", value->u.literal_string);
	}
	return v;
}

void js_print_array(JsArray *array)
{
	if (NULL == array || 0 == array->length)
	{
		return;
	}
	int i;
	printf("[");
	for (i = 0; i < array->length; i++)
	{
		js_print(array->elements + i);
		if (i < array->length - 1)
		{
			printf(",");
		}
	}
	printf("]");
}

JsValue js_println(const JsValue *value)
{
	JsValue v;
	v.typ = JS_VALUE_TYPE_NULL;
	v = js_print(value);
	printf("\n");
	return v;
}

JsValue js_typeof(const JsValue *value)
{
	JsValue v;
	v.typ = JS_VALUE_TYPE_STRING_LITERAL;
	switch (value->typ)
	{
	case JS_VALUE_TYPE_BOOL:
		v.u.literal_string = "bool";
		break;
	case JS_VALUE_TYPE_INT:
		v.u.literal_string = "int";
		break;
	case JS_VALUE_TYPE_FLOAT:
		v.u.literal_string = "float";
		break;
	case JS_VALUE_TYPE_STRING:
		v.u.literal_string = "string";
		break;
	case JS_VALUE_TYPE_NULL:
		v.u.literal_string = "null";
		break;
	case JS_VALUE_TYPE_UNDEFINED:
		v.u.literal_string = "undefined";
		break;
	case JS_VALUE_TYPE_ARRAY:
		v.u.literal_string = "array";
		break;
	case JS_VALUE_TYPE_FUNCTION:
		v.u.literal_string = "function";
		break;
	case JS_VALUE_TYPE_OBJECT:
		v.u.literal_string = "object";
		break;
	case JS_VALUE_TYPE_STRING_LITERAL:
		v.u.literal_string = "string_literal";
	}
	return v;
}
