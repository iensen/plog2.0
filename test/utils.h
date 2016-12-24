//
// Created by iensen on 12/23/16.
//

#ifndef PLOG_UTILS_H
#define PLOG_UTILS_H

#include<string>
#include <gtest/internal/gtest-port.h>
#include "../plogapp/src/plog_app.h"


std::string find_trailing_number(std::string out) {
    int index = 0;
    while(!isdigit(out[index])) ++ index;
    return out.substr(index);
}

double stringtoDouble(const std::string &s) {
    std::stringstream ss;
    ss << s;
    double x;
    ss >> x;
    return x;
}

double run_plog(std::string file) {
    PlogApp app;
    char ** f = new char*[3];
    f[1] = new char[file.length()+1];
    f[0] = new char[5];
    f[2] = nullptr;
    strcpy(f[0],"plog");
    strcpy(f[1],file.c_str());
    testing::internal::CaptureStdout();
    app.main(2, f);
    std::string output = testing::internal::GetCapturedStdout();
    delete[] f[0];
    delete[] f[1];
    delete[] f;
    return stringtoDouble(find_trailing_number(output));

}


double run_old_plog(std::string file) {
    return 0.0;
}



#endif //PLOG_UTILS_H
