# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 11:47:33 by echavez-          #+#    #+#              #
#    Updated: 2024/04/21 10:33:38 by echavez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=   cub3d

#****************** INC *******************#
# General
INC			=   ./include/				# Project header files drectory

# Libft
LIB         =   ./lib/libft/			# Library to include
LIB_H       =   ./lib/libft/			# Library header files directory

# Minilibx
LIBMLX		=   ./lib/minilibx-linux/	# Library to include
LIBMLX_H	=   ./lib/minilibx-linux/	# Library header files directory

INCLUDE		=   -O3 -I $(LIB_H) -I $(LIBMLX_H) -I $(INC)

LIB_INC		=   -L$(LIB) -lft -L$(LIBMLX) -lmlx -lXext -lX11 -lm -lbsd

#****************** SRC *******************#

DIRSRC      =   ./src/
DIRCONFIG       :=  $(DIRSRC)config/
DIRGAME         :=  $(DIRSRC)game/
DIRRAYCASTING   :=  $(DIRSRC)raycasting/
DIRSTRUCTURES   :=  $(DIRSRC)structures/

DIRS        :=  $(DIRSRC) $(DIRCONFIG) $(DIRGAME) $(DIRRAYCASTING) $(DIRSTRUCTURES)

SRC         =   main.c
CONFIG      =   check_map.c load_config.c check_element.c load_config_utils.c
GAME        =   game.c image.c hooks.c bmp.c render.c move.c turn.c bmp_conversions.c
RAYCASTING  =   raycasting.c distance.c bmp_3d.c texture.c
STRUCTURES  =   cub3d.c destructors.c graphic_destructor.c map_destructor.c llmap.c map.c

SRCS        :=  $(SRC) $(CONFIG) $(GAME) $(RAYCASTING) $(STRUCTURES)

#***************** DEPS ******************#

DIROBJ      =   ./depo/

#********************************* END OF CONFIG *********************************#

OAUX        =   $(SRCS:%=$(DIROBJ)%)
DEPS        =   $(OAUX:.c=.d)
OBJS        =   $(OAUX:.c=.o)

.ONESHELL:

$(info Creating directory...)
$(shell mkdir -p $(DIROBJ))

ifdef FLAGS
    ifeq ($(FLAGS), no)
CFLAGS      =
    endif
    ifeq ($(FLAGS), debug)
CFLAGS      =   -Wall -Wextra -Werror -ansi -pedantic -g -fsanitize=address
    endif
else
CFLAGS      =   -Wall -Wextra -Werror
endif

ifdef VERB
    ifeq ($(VERB), on)
CFLAGS      +=  -DM_VERB
    endif
endif

ifndef VERBOSE
.SILENT:
endif

ENV         =   /usr/bin/env
CC          =   $(ENV) clang
RM          =   $(ENV) rm -rf
ECHO        =   $(ENV) echo -e
MKDIR       =   $(ENV) mkdir -p
GIT         =   $(ENV) git
BOLD        =   "\e[1m"
REVER       =   "\e[7m"
BLINK       =   "\e[5m"
RED         =   "\e[38;2;255;0;0m"
GREEN       =   "\e[92m"
BLUE        =   "\e[34m"
YELLOW      =   "\e[33m"
E0M         =   "\e[0m"

FMT         :=  $(REVER)$(YELLOW)$(BLINK)

#******************************* DEPS COMPILATION ********************************#

define generate_objects
$(DIROBJ)%.o    :   $(1)%.c
	                @printf $(GREEN)"Generating $(NAME) objects... %-33.33s\r"$(E0M) $$@
	                @$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $$@ -c $$<
endef

# Generate objects
$(foreach dir,$(DIRS),$(eval $(call generate_objects,$(dir))))

#******************************* MAIN COMPILATION ********************************#

$(NAME)         :       ftlib $(OBJS)
	                @$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_INC)
	                @$(ECHO)
	                @$(ECHO) '                       '$(FMT)'██████'$(E0M)
	                @$(ECHO) '                   '$(FMT)'████░░░░░░██'$(E0M)
	                @$(ECHO) '                 '$(FMT)'██░░░░░░░░██'$(E0M)
	                @$(ECHO) '               '$(FMT)'██░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '   '$(FMT)'████████░░░░░░░░░░░░░░░░░░░░░░░░████████'$(E0M)
	                @$(ECHO) ' '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) ' '$(FMT)'██▓▓░░░░░░░░░░░░  ██░░░░  ██░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '   '$(FMT)'██▓▓░░░░░░░░░░████░░░░████░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '     '$(FMT)'██▓▓░░░░░░░░████░░░░████░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░▓▓██░░░░██▓▓░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██▓▓░░▓▓████████████▓▓░░▓▓██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██▓▓██'$(E0M)'            '$(FMT)'██▓▓██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██'$(E0M)'                '$(FMT)'██'$(E0M)
	                @$(ECHO) $(E0M)
	                @$(ECHO) $(BOLD)$(GREEN)'> '$(NAME)' Compiled'$(E0M)

$(OBJS): | mkdepo

clean           :
	                @($(RM) $(OBJS))
	                @($(RM) $(DEPS))
	                @($(RM) $(DIROBJ))
	                @(cd $(LIB) && $(MAKE) clean)
					@(cd $(LIBMLX) && $(MAKE) clean)
	                @$(ECHO) $(BOLD)$(RED)'> '$(NAME)' directory        cleaned'$(E0M)

all             :       $(NAME)

fclean          :       clean
	                @$(RM) $(NAME)
	                @(cd $(LIB) && $(MAKE) fclean)
					@(cd $(LIBMLX) && $(MAKE) fclean)
	                @$(ECHO) $(BOLD)$(RED)'> Executable             removed'$(E0M)


re              :  fclean mkdepo all

mkdepo			:
					@$(MKDIR) $(DIROBJ)


ftlib           :
	                @(cd $(LIB) && $(MAKE))
					@(cd $(LIBMLX) && $(MAKE))

init            :
	                @$(GIT) submodule init
	                @$(GIT) submodule update

.PHONY          :       all clean re fclean ftlib

-include $(DEPS)