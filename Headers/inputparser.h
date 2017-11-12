#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <vector>
#include <string>
#include <qstringlist.h>


class InputParser
{
public:
    InputParser(int &argc, char **argv);
    InputParser(QStringList &list);
    const std::string& getCmdOption(const std::string &option);
    bool cmdOptionExists(const std::string &option);

private:
    std::vector<std::string> tokens;
};

#endif // INPUTPARSER_H
