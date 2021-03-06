# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    default_vars.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mataiaz <mataiaz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 13:39:47 by mfischer          #+#    #+#              #
#    Updated: 2021/01/20 04:12:21 by mataiaz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	g++

#*#*#*#*# CHANGE PROGRAM NAME HERE #*#*#*#*#
NAME			:=	MapBuilder
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*

CFLAGS			:=	-Wall -Werror -Wextra -std=c++20

CLIBS			+= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

BLACK_LIST_SRCS :=	

SRCDIRS			:=	srcs

SRCS			+=	$(shell find $(SRCDIRS) -name '*.cpp')

INC_PATHS		:=	includes

INC_PATHS		:=	$(shell find $(INC_PATHS) -type d)

INCLUDES		+=	$(foreach d, $(INC_PATHS), -I $d)

SRC_DIR			:=	$(patsubst srcs/%,obj/%,$(shell find srcs/* -type d))

OBJS			:=	$(patsubst srcs/%.cpp,obj/%.o,$(SRCS))

DEPS			:=	$(patsubst %.o,%.d,$(OBJS))

UNAME			:=	$(shell uname -s)

INC_DIRS		+=	mfGUI/includes

INC_DIRS		:= $(foreach d, $(INC_DIRS), -I $d)

LIBDEP			:=	mfGUI/mfGUI.a


# This is a minimal set of ANSI/VT100 color codes
_END			=	\033[0;0m
_BOLD			=	\033[0;1m
_UNDER			=	\033[0;4m
_REV			=	\033[0;7m

# Colors
_GREY			=	\033[0;30m
_RED			=	\033[0;31m
_GREEN			=	\033[0;32m
_YELLOW			=	\033[0;33m
_BLUE			=	\033[0;34m
_PURPLE			=	\033[0;35m
_CYAN			=	\033[0;36m
_WHITE			=	\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY			=	\033[0;40m
_IRED			=	\033[0;41m
_IGREEN			=	\033[0;42m
_IYELLOW		=	\033[0;43m
_IBLUE			=	\033[0;44m
_IPURPLE		=	\033[0;45m
_ICYAN			=	\033[0;46m
_IWHITE			=	\033[0;47m