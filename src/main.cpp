
// 解决旧API编译错误问题
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

#include <iostream>
#include <fstream>
#include <cassert>

#include "json/json.h"

void OldAPIDemo()
{
    // old api writer
    {
        Json::Value root;
        Json::Value person;

        // [{"age":35,"name":"Tellen","school":"nuaa"}]
        person["name"] = "Tellen";
        person["age"] = 35;
        person["school"] = "nuaa";
        root.append(person);

        Json::FastWriter fast_writer;
        std::string json_no_style = fast_writer.write(root);
        std::cout << "~~~~~~Json::FastWriter:" << std::endl;
        std::cout << json_no_style << std::endl;

        Json::StyledWriter styled_writer;
        std::string json_styled = styled_writer.write(root);
        std::cout << "~~~~~~Json::StyledWriter:" << std::endl;
        std::cout << json_styled << std::endl;

        std::ofstream ofs;
        ofs.open("test.json");
        assert(ofs.is_open());
        //ofs << json_styled;
        //ofs.close();

        Json::StyledStreamWriter styled_stream_writer;
        std::cout << "~~~~~~Json::StyledStreamWriter:" << std::endl;
        styled_stream_writer.write(std::cout, root);
        styled_stream_writer.write(ofs, root);
        ofs.close();

        std::cout << "toStyledString:\n" << root.toStyledString();
    }

    // old api reader
    {
        std::ifstream ifs;
        ifs.open("test.json");
        assert(ifs.is_open());

        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(ifs, root, false))
        {
            std::cout << "parse error" << std::endl;
            ifs.close();
            return;
        }
        ifs.close();

        std::cout << "~~~~~~Json::Reader:" << std::endl;
        std::string name;
        int age;
        int size = root.size();
        for (int i = 0; i < size; ++i)
        {
            name = root[i]["name"].asString();
            age = root[i]["age"].asInt();

            std::cout << "name: " << name << std::endl;
            std::cout << "age: " << age << std::endl;
        }

        std::cout << "~~~~~~Json::Value::iterator:" << std::endl;
        Json::Value::Members member; // std::vector<string>
        for (Json::Value::iterator itr = root.begin(); itr != root.end(); ++itr)
        {
            member = (*itr).getMemberNames();
            for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter)
            {
                std::string str_temp = (*itr)[(*iter)].asString();
                std::cout << "iterator: " << str_temp << std::endl;
            }
        }
    }
}

void CreatJsonNewAPI()
{
    Json::Value root;
    Json::Value lang;
    Json::Value work;

    root["name"] = "tellen";
    root["age"] = 35;

    lang[0] = "C++";
    lang[1] = "python";
    lang[2] = "java";
    root["language"] = lang;

    work["work1"] = "nrist";
    work["work2"] = "palmap";
    work["work3"] = "sn";
    root["work"] = work;

    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream oss;
    //writerBuilder.settings_["indentation"] = ""; // 非格式化输出
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &oss);
    std::cout << "~~~~~~New API:\n"
              << oss.str() << std::endl;

    std::cout << "~~~~~~std::cout:" << std::endl;
    jsonWriter->write(root, &std::cout);
}

bool ParseJsonNewAPI(const std::string &str_json)
{
    if (str_json.empty())
    {
        std::cout << "~~~~~~ParseJsonNewAPI error input null" << std::endl;
        return false;
    }

    bool res;
    JSONCPP_STRING errs;
    Json::Value root;
    Json::Value lang;
    Json::Value work;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(str_json.c_str(), str_json.c_str() + str_json.length(), &root, &errs);
    if (!res || !errs.empty())
    {
        std::cout << "~~~~~~ParseJsonNewAPI error. " << errs << std::endl;
        return false;
    }

    std::cout << "~~~~~~ParseJsonNewAPI:" << std::endl;
    std::cout << "name: " << root["name"].asString() << std::endl;
    std::cout << "age: " << root["age"].asInt() << std::endl;

    lang = root["language"];
    std::cout << "language: ";
    for (int i = 0; i < lang.size(); ++i)
    {
        std::cout << lang[i] << " ";
    }
    std::cout << std::endl;

    work = root["work"];
    std::cout << "work1: " << work["work1"].asString() << std::endl;
    std::cout << "work2: " << work["work2"].asString() << std::endl;
    std::cout << "work3: " << work["work3"].asString() << std::endl;

    // 判断key是否存在
    bool is_age = root.isMember("age");
    std::cout << "isMember:" << std::boolalpha << is_age << std::endl;

    // 得到所有的key
    std::cout << "keys: ";
    for (auto elem : root.getMemberNames())
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 删除成员
    root.removeMember("age");

    // 得到所有的key
    std::cout << "keys: ";
    for (auto elem : root.getMemberNames())
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return true;
}

int main(int argc, char *argv[])
{
    OldAPIDemo();

    CreatJsonNewAPI();

    std::string str_json = "{\"age\":35,\"language\":[\"C++\",\"python\",\"java\"],\"name\":\"tellen\",\"work\":{\"work1\":\"nrist\",\"work2\":\"palmap\",\"work3\":\"sn\"}}";
    ParseJsonNewAPI(str_json);
    str_json = "abc";
    ParseJsonNewAPI(str_json);

    return 0;
}