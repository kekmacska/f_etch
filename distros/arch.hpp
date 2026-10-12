#pragma once
#include <string_view>

#define RESET_ARCH "\x1b[0m"
#define ARCH_COLOR "\x1b[38;2;23;147;209m"

using namespace std;

inline constexpr string_view archlogo_screenfetch = ARCH_COLOR
R"(
                   -`
                  .o+`
                 `ooo/
                `+oooo:
               `+oooooo:
               -+oooooo+:
             `/:-:++oooo+:
            `/++++/+++++++:
           `/++++++++++++++:
          `/+++ooooooooooooo/`
         ./ooosssso++osssssso+`
        .oossssso-````/ossssss+`
       -osssssso.      :ssssssso.
      :osssssss/        osssso+++.
     /ossssssss/        +ssssooo/-
   `/ossssso+/:-        -:/+osssso+-
  `+sso+:-`                 `.-/+oso:
 `++:.                           `-/+/
 .`                                 `
)"
RESET_ARCH;

inline constexpr string_view archlogo_hashtag = ARCH_COLOR
R"(
                  ##
                 ####
                ######
               ########
              ##########
             ############
            ##############
           ################
          ##################
         ####################
        ######################
       #########      #########
      ##########      ##########
     ###########      ###########
    ##########          ##########
   #######                  #######
  ####                          ####
 ###                              ###
)"
RESET_ARCH;

inline constexpr string_view archlogo_hashtag_edge = ARCH_COLOR
R"(
                    -@                
                   .##@               
                  .####@              
                  @#####@             
                . *######@            
               .##@o@#####@           
              /############@          
             /##############@         
            @######@**%######@        
           @######`     %#####o       
          @######@       ######%      
        -@#######h       ######@.`    
       /#####h**``       `**%@####@   
      @H@*`                    `*%#@  
     *`                            `* 
)"
RESET_ARCH;

inline constexpr string_view archlogo_fullblock = ARCH_COLOR
R"(
                   ▄
                  ▟█▙
                 ▟███▙
                ▟█████▙
               ▟███████▙
              ▂▔▀▜██████▙
             ▟██▅▂▝▜█████▙
            ▟█████████████▙
           ▟███████████████▙
          ▟█████████████████▙
         ▟███████████████████▙
        ▟█████████▛▀▀▜████████▙
       ▟████████▛      ▜███████▙
      ▟█████████        ████████▙
     ▟██████████        █████▆▅▄▃▂
    ▟██████████▛        ▜█████████▙
   ▟██████▀▀▀              ▀▀██████▙
  ▟███▀▘                       ▝▀███▙
 ▟▛▀                               ▀▜▙
)"
RESET_ARCH;

inline constexpr string_view archlogo_outline = ARCH_COLOR
R"(
                    .
                   / \
                  /   \
                 /     \
                /.      \
               ,_ `.     \
              /   ``-     .
             /             `
            /               `.
          .`      ."`".       \
         .       '     \       \
        /        \      ;     -.\
       /        .'     /._     `".
      /   .-"`             `"-.   `.
    .`.-`                       `-._\
    `                               `
)"
RESET_ARCH;

inline constexpr string_view archlogo_outline_small = ARCH_COLOR
R"(
            /\
           /  \
          /    \
         _\     \
        /        \
       /          \
      /     __   \_\
     /     /  \     \
    /__,--'    '--,__\
)"
RESET_ARCH;