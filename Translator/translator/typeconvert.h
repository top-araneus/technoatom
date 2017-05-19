#ifndef TYPECONVERT_H
#define TYPECONVERT_H

/*! @fn T fromString(const std::string& s)
    @brief Converts string value to defined type and returns it */
template<typename T>
T fromString(const std::string& s)
{
    std::istringstream iss(s);
    T res;
    iss >> res;
    return res;
}

#endif // TYPECONVERT_H
