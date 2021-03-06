/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_server.cc
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 16:43:11
 * @brief 
 *  
 **/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "node_manager.h"
#include "name_service.h"
#include "common/tools.h"
#include "common/ds_log.h"
#include "config/config_manager.h"

using namespace dist_storage;
using namespace dist_storage::name_server;
using namespace PUBLIC_UTIL;

inline void InitSignal() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    if (-1 == sigaction(SIGPIPE, &sa, NULL)) {
        exit(1);
    }
}

inline void Daemonize() {
    if (0 != fork()) {
        exit(0);
    }
    if (-1 == setsid()) {
        fprintf(stderr, "set sid error!\n");
        exit(-1);
    }
    umask(0);
    int fd = open("/dev/null", O_RDWR, 0);
    if (-1 != fd) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }
}

int main(int argc, char* argv[]) {
    InitSignal();

    if (true) {
         Daemonize();
    }
    if (!DS_SYS_CONF.ConfigInit("../conf/name_server.ini")) {
        DS_LOG(ERROR, "Name server init the data server config failed!");
        return 0;
    }
    const char* log_dir = DS_SYS_CONF.IniGetString("log:path");

    if (!CreateDir(log_dir)) {
        DS_LOG(ERROR, "Name server create log dir: %s faied!", log_dir);
        return 0;
    }
    if (false == DSLogInit(
                argc, argv, DS_SYS_CONF.IniGetString("log:level"), log_dir)) {
        return 0;
    }
    GlobalNM.Start();

    NameServiceThread ns_thread;
    ns_thread.Start();

    ns_thread.Wait();
    GlobalNM.Wait();


    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
