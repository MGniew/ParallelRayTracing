#include "inputparser.h"
#include "iostream"

InputParser::InputParser(int &argc, char **argv)
{
    for (int i=1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
}

InputParser::InputParser(QStringList &list)
{
    QStringList::Iterator it;
    for(it = list.begin(); it != list.end(); ++it){
        std::cout << (*it).toStdString() << std::endl;
        this->tokens.push_back((*it).toStdString());
    }
}

const std::string &InputParser::getCmdOption(const std::string &option)
{
    std::vector<std::string>::const_iterator itr;
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::cmdOptionExists(const std::string &option)
{
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}
