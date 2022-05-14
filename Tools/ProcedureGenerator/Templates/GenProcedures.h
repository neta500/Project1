// this file is auto generated file. do not edit!

#pragma once
#include "DBBind.h"

{%- macro gen_procedures() -%} {% include 'Procedure.h' %} {% endmacro %}

namespace SP
{
	{{gen_procedures() | indent}}
};