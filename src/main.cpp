
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

int main(int argc, char *argv[])
{
    // old api writer
    {
        Json::Value root;
        Json::Value person;

        // [{"age":35,"name":"Tellen"}]
        person["name"] = "Tellen";
        person["age"] = 35;
        person["school"] = "nuaa";
        root.append(person);

        Json::FastWriter writer;
        std::string json_no_style = writer.write(root);
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
            return -1;
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

    return 0;
}