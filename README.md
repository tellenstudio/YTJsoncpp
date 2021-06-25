# YTJsoncpp

jsoncpp中主要的类：

- **Json::Value**：可以表示所有支持的类型，如：int , double ,string , object, array等。其包含节点的类型判断(isNull,isBool,isInt,isArray,isMember,isValidIndex等),类型获取(type),类型转换(asInt,asString等),节点获取(get,[]),节点比较(重载<,<=,>,>=,==,!=),节点操作(compare,swap,removeMember,removeindex,append等)等函数。
- **Json::Reader**：将文件流或字符串创解析到Json::Value中，主要使用parse函数。Json::Reader的构造函数还允许用户使用特性Features来自定义Json的严格等级。
	- 使用Json::Reader对json文件进行解析
bool parse(const std::string& document, Value& root, bool collectComments = true);
参数：document: 包含要读取的文档的UTF-8编码字符串
root:（输出）Json::Value的对象
	- 使用Json::Reader对json输入流（文件）进行解析
bool parse(std:stream& is, Value& root, bool collectComment = true);
	- 使用Json::Reader对字符串进行解析
bool parse(const char* beginDoc, const char* ednDoc, Value& root, bool collectComment = true);
- **Json::Writer**：与JsonReader相反，将Json::Value转换成字符串流等，Writer类是一个纯虚类，并不能直接使用。在此我们使用Json::Writer的子类：Json::FastWriter(将数据写入一行,没有格式，速度快),Json::StyledWriter(按json格式化输出,易于阅读)。
- JsonCpp其他操作
	- 判断key是否存在: bool Json::Value::isMember(const char * key) const；存在返回1，否则返回0
	- 判断是否为null成员函数: bool Json::Value::isNull() const; 和C++中的map有一个共同的特点，就是当你尝试访问一个不存在的key时，会自动生成这样一个key-value默认为null的值对。
	- 得到所有成员:
typedef std::vectorstd::string Json::Value::Members;
Value::Members Json::Value::getMemberNames() const;
该函数的类型为一个string的vector。
	- 删除成员: Value Json::Value::removeMember(const char* key) 返回删除的值，或者null


Json::Value()常用成员函数

	  String asString() const;
	  Int asInt() const;
	  UInt asUInt() const;
	  Int64 asInt64() const;
	  UInt64 asUInt64() const;
	  LargestInt asLargestInt() const;
	  LargestUInt asLargestUInt() const;
	  float asFloat() const;
	  double asDouble() const;
	  bool asBool() const;

	  bool isNull() const;
	  bool isBool() const;
	  bool isInt() const;
	  bool isInt64() const;
	  bool isUInt() const;
	  bool isUInt64() const;
	  bool isIntegral() const;
	  bool isDouble() const;
	  bool isNumeric() const;
	  bool isString() const;
	  bool isArray() const;
	  bool isObject() const;

	enum ValueType {
	  nullValue = 0, ///< 'null' value
	  intValue,      ///< signed integer value
	  uintValue,     ///< unsigned integer value
	  realValue,     ///< double value
	  stringValue,   ///< UTF-8 string value
	  booleanValue,  ///< bool value
	  arrayValue,    ///< array value (ordered list)
	  objectValue    ///< object value (collection of name/value pairs).
	};
