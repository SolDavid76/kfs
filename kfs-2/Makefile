NAME		=	$(NAME_BIN) $(NAME_ISO)

NAME_BIN	=	kfs-2.bin
NAME_ISO	=	kfs-2.iso

################################# SOURCE FILES #################################

SRC_C		=	kernel.c\
				print.c\
				utils.c\

SRC_ASM		=	boot.s\
				load_gdt.s\

SRCDIR		=	srcs/

INCLUDES	=	includes/

SRCS_ASM	=	$(addprefix $(SRCDIR), $(SRC_ASM))
SRCS_C		=	$(addprefix $(SRCDIR), $(SRC_S))

################################### OBJECTS ####################################

OBJDIR		=	objs/

OBJS		=	$(OBJS_ASM) $(OBJS_C) 

OBJS_ASM	=	$(addprefix $(OBJDIR), $(SRC_ASM:.s=.o))
OBJS_C		=	$(addprefix $(OBJDIR), $(SRC_C:.c=.o))


################################## COMPILERS ###################################

NASM		=	nasm -f elf32

LD			=	ld

LD_FLAGS	=	-m elf_i386 -T linker.ld

CC			=	gcc

RM			=	rm -rf

CFLAGS		=	-m32\
				-fno-builtin\
				-fno-exceptions\
				-fno-stack-protector\
				-nostdlib\
				-nodefaultlibs\

#################################### RULES #####################################

all:	$(NAME)

$(OBJDIR): 
		mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.s
		$(NASM) $< -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c 
		$(CC) -g3 -c $(CFLAGS) -I $(INCLUDES) $< -o $@

$(NAME): $(OBJDIR) $(OBJS)
		$(LD) $(LD_FLAGS) $(OBJS) -o $(NAME_BIN) -I $(INCLUDES)
		mkdir -p iso/boot/grub
		cp $(NAME_BIN) iso/boot
		cp grub.cfg iso/boot/grub
		grub-mkrescue -o $(NAME_ISO) iso/

clean:
		$(RM) $(OBJDIR) 
		$(RM) iso/

fclean:	clean
		$(RM) $(NAME)

run: $(NAME)
		qemu-system-i386 -kernel $(NAME_BIN)

run_iso: $(NAME)
		qemu-system-i386 -cdrom $(NAME_ISO)

re:	fclean all

.PHONY:	clean fclean all re
 
