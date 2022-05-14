{%- macro lower_first(text) %}{{text[0]|lower}}{{text[1:]}}{% endmacro -%}

{%- for proc in procs %}
class {{proc.name}} : public DBBind<{{proc.params|length}},{{proc.columns|length}}>
{
public:
	{{proc.name}}(DBConnection& conn) : DBBind(conn, L"{CALL dbo.{{ proc.name }}{{ proc.questions }}}") {}

{%- for param in proc.params %}
  {%- if param.type == 'nvarchar' %}
	template<int N> void In_{{param.name}}(wchar_t(&v)[N]) { BindParam({{loop.index - 1}}, v); }
	template<int N> void In_{{param.name}}(const wchar_t(&v)[N]) { BindParam({{loop.index - 1}}, v); }
	void In_{{param.name}}(wchar_t* v, int count) { BindParam({{loop.index - 1}}, v, count); }
	void In_{{param.name}}(const wchar_t* v, int count) { BindParam({{loop.index - 1}}, v, count); }
  {%- elif param.type == 'varbinary' %}
	template<typename T, int N> void In_{{param.name}}(T(&v)[N]) { BindParam({{loop.index - 1}}, v); }
	template<typename T> void In_{{param.name}}(T* v, int count) { BindParam({{loop.index - 1}}, v, count); }
  {%- else %}
	void In_{{param.name}}({{param.type}}& v) { BindParam({{loop.index - 1}}, v); }
	void In_{{param.name}}({{param.type}}&& v) { _{{lower_first(param.name)}} = std::move(v); BindParam({{loop.index - 1}}, _{{lower_first(param.name)}}); }
  {%- endif %}
{%- endfor %}

{%- for column in proc.columns %}
  {%- if column.type == 'nvarchar' %}
	template<int N> void Out_{{column.name}}(wchar_t(&v)[N]) { BindCol({{loop.index - 1}}, v); }
  {%- elif column.type == 'varbinary' %}
	template<typename T, int N> void Out_{{column.name}}(T(&v)[N]) { BindCol({{loop.index - 1}}, v); }
  {%- else %}
	void Out_{{column.name}}({{column.type}}& v) { BindCol({{loop.index - 1}}, v); }
  {%- endif %}
{%- endfor %}

private:
{%- for param in proc.params %}
  {%- if param.type == 'int' or param.type == 'TIMESTAMP_STRUCT' %}
	{{param.type}} _{{lower_first(param.name)}} = {};
  {%- endif %}
{%- endfor %}
};
{% endfor %}


