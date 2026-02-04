#include "help.hpp"
#include <cstdio>

void print_help() {
    printf("* Welcome to Rungo!\n"
           "* Rungo is the official package manager for Korelin.\n"
           "\nRungo usage:\n"
           "\n    rungo <command> [arguments]\n"
           "\nThe commands are:\n\n"
           "    install <package-name>    Install a Korelin package (-i: use mirror URL)\n"
           "    uninstall <package-name>  Uninstall a specified Korelin package\n"
           "    list                      List all installed Korelin packages\n"
           "    init <project-name>       Initialize a new Korelin project (Rungo)\n");
}
