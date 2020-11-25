make && clang -o miniRT -Iheaders -Ilibft -IminilibX -LminilibX -lXext -lX11 -lm -lbsd srcs/main.c lib/miniRT.a minilibX/libmlx.a
