/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:32:55 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/01 21:42:18 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <mlx.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

//PRINTF
#include <stdio.h>
//PRINTF

#define MAX_OBJECTS 	100
#define MAX_LIGHTS		10
#define MAX_CAMERAS		10
#define MAX_RESX		1920
#define	MAX_RESY		1080
#define BITS_PER_PIXEL	32
#define ENDIAN			0

typedef	enum	e_objects
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE,
	LIGHT,
	AMBLIGHT,
	CAMERA,
	RESOLUTION
}				te_objects;

typedef enum	e_coordstype
{
	ORI,
	POS
}				t_coordstype;

typedef enum	e_dimensions
{
	X,
	Y,
	Z
}				te_dimensions;

typedef enum	e_faces
{
	INTERIOR,
	EXTERIOR
}				te_faces;

typedef struct	s_matrix3
{
	double	v[3][3];
}				t_matrix3;

typedef struct	s_matrix
{
	double	v[4][4];
}				t_matrix;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_coords
{
	double	x;
	double	y;
	double	z;
}				t_coords;

typedef struct	s_coords_cp
{
	double	r;
	double	t;
	double	z;
}				t_coords_cp;

typedef struct	s_camera
{
	t_coords	pos;
	t_coords	ori;
	int			fov;
}				t_camera;

typedef struct	s_light
{
	t_coords	pos;
	t_color		rgb;
	int			color;
	double		lum;
}				t_light;

typedef struct	s_sphere
{
	int			type;
	t_coords	pos;
	double		diameter;
	double		radius;
	t_color		rgb;
	int			color;
}				t_sphere;

typedef struct	s_cylinder
{
	int			type;
	t_matrix	Ti;
	t_matrix	Ri;
	t_matrix	Si;
	t_coords	pos;
	t_coords	ori;
	double		radius;
	double		height;
	t_color		rgb;
	int			color;
	int			lastfacehit;
}				t_cylinder;

typedef struct	s_plane
{
	int			type;
	t_coords	pos;
	t_coords	ori;
	t_coords	norm;
	t_color		rgb;
	int			color;
}				t_plane;

typedef struct	s_square
{
	int			type;
	t_coords	pos;
	t_coords	ori;
	t_coords	norm;
	t_coords	e1;
	t_coords	e2;
	double		height;
	double		height2;
	t_color		rgb;
	int			color;
}				t_square;

typedef struct	s_triangle
{
	int			type;
	t_coords	v1;
	t_coords	v2;
	t_coords	v3;
	t_coords	norm;
	t_color		rgb;
	int			color;
}				t_triangle;

typedef union	u_object
{
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_square	square;
	t_cylinder	cylinder;
	t_triangle	triangle;
}				t_object;

typedef struct	s_screen
{
	double	tfov2;
	double	aspect_ratio;
	int		width;
	int		height;
	void	*mlx;
	void	*window;
}				t_screen;

typedef struct	e_image
{
	void		*ptr;
	void		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_scene
{
	t_object	objects[MAX_OBJECTS];
	t_light		lights[MAX_LIGHTS];
	t_light		amblight;
	t_camera	cameras[MAX_CAMERAS];
	t_image		images[MAX_CAMERAS];
	t_matrix	*ctw_matrix;
	t_screen	screen;
	int			camselect;
	int			cam_count;
	int			light_count;
	int			obj_count;
	int			res_set;
	int			amb_set;
}				t_scene;

typedef struct	s_ray
{
	t_coords	pos;
	t_coords	dir;
}				t_ray;

typedef struct	s_surf_pt
{
	t_coords	pos;
	double		d_to_ori;
	int			iobj;
	int			color;
}				t_surf_pt;

t_color		ft_getrgb(int color);
t_matrix	*ft_mat_rot(t_coords *c);
t_matrix	*ft_mat_rotx(double a);
t_matrix	*ft_mat_roty(double a);
t_matrix	*ft_mat_rotz(double a);
t_matrix	*ft_mat_trans(t_coords *c);
t_matrix	*ft_mat_scal(t_coords *c);
t_matrix	*ft_mat_mlt(t_matrix *m1, t_matrix *m2);
t_matrix	*ft_mat_adj(t_matrix *m);
t_matrix	*ft_mat_inv(t_matrix *m);
t_matrix3	*ft_mat4tomat3(t_matrix *m, int l, int c);
double		ft_mat_det(t_matrix *m);
double		ft_mat3_det(t_matrix3 *m);
double		ft_dist(t_coords *a, t_coords *b);
double		ft_dot(t_coords *a, t_coords *b);
int			ft_getcolor(t_color *rgb);
int			ft_intersect(t_ray *ray, t_object *object, double *solution);
int			ft_quadratic_eq(double coeffs[3], double *solutions);
int			ft_ray_tracer(t_scene *scene, unsigned char *data_addr);
int			ft_getobjtype(char *line);
int			ft_isvalid_intendc(char *s, const char *c);
int			ft_isvalid_int(char *s);
int			ft_isvalid_db(char *s);
int			ft_isvalid_rgb(char *s);
int			ft_isvalid_3db(char *s);
int			ft_isvalid_res(char **a);
int			ft_isvalid_alight(char **a);
int			ft_isvalid_cam(char **a);
int			ft_isvalid_light(char **a);
int			ft_isvalid_sphere(char **a);
int			ft_isvalid_plane(char **a);
int			ft_isvalid_square(char **a);
int			ft_isvalid_cyl(char **a);
int			ft_isvalid_triangle(char **a);
int			ft_isvalid_splitline(int objtype, char **a);
int			ft_isvalid_fov(int fov);
int			ft_isvvalid_rgb(t_color color);
int			ft_isvvalid_ori(t_coords ori);
int			ft_isvvalid_lum(double lum);
int			ft_parse_color(t_color *color, const char *s);
int			ft_parse_coords(t_coords *c, const char *s, int ctype);
int			ft_parse_res(char **a, t_scene *scene);
int			ft_parse_line(char *line, t_scene *scene);
int			ft_parse_cam(char **a, t_scene *scene);
int			ft_parse_sphere(char **a, t_scene *scene);
int			ft_parse_plane(char **a, t_scene *scene);
int			ft_parse_cylinder(char **a, t_scene *scene);
int			ft_parse_square(char **a, t_scene *scene);
int			ft_parse_triangle(char **a, t_scene *scene);
int			ft_parse_amblight(char **a, t_scene *scene);
int			ft_parse_light(char **a, t_scene *scene);
int			ft_parse_file(t_scene *scene, char *filename);
int			ft_screenshot(t_scene *scene, char *filename);
int			ft_draw_image(t_scene *scene, int camselect);
int			ft_draw_all_images(t_scene *scene);
int			ft_close(void);
int			ft_key_hook(int keycode, void *param);
int			ft_isqnscissq_inter_positive(t_coords *p1, t_coords *p2);
int			ft_oddeven_vertices_test(t_coords v[3]);
int			ft_oddeven_test(t_coords point, t_object tr);
int			ft_intersect_sphere(t_ray *ray, t_object *object, double *solution);
int			ft_intersect_cylinder(t_ray *ray, t_object *object, double *solution);
int			ft_intersect_plane(t_ray *ray, t_object *object, double *solution);
int			ft_intersect_square(t_ray *ray, t_object *object, double *solution);
int			ft_intersect_triangle(t_ray *ray, t_object *object, double *solution);
t_coords	ft_cross(t_coords *a, t_coords *b);
t_coords	ft_coo_sub(t_coords *a, t_coords *b);
t_coords	ft_coo_add(t_coords *a, t_coords *b);
t_coords	ft_coo_mlt(t_coords *a, double b);
t_camera	ft_mkcamera(t_coords pos, t_coords ori);
t_object	ft_mkplane(t_coords pos, t_coords ori, int color);
t_object	ft_mksphere(t_coords pos, double diameter, int color);
t_object	ft_mksquare(t_coords pos, t_coords ori, double height, int color);
t_object	ft_mkcylinder(t_coords pos, t_coords ori, double height, double radius, int color);
t_object	ft_mktriangle(t_coords *vertices, int color);
t_light		ft_mklight(t_coords pos, int color, double lum);
t_image		ft_mkimage(t_screen *screen);
void		ft_normalize(t_coords *a);
void		ft_print_coords(t_coords c);
void		ft_print_matrix(t_matrix *matrix);
void		ft_print_matrix3(t_matrix3 *m);
void		ft_print_coordscp(t_coords_cp c);
void		ft_print_screen(t_screen *screen);
void		ft_print_scene(t_scene *scene);
void		ft_print_rgb(t_color *rgb);
void		ft_print_camera(t_camera *cam);
void		ft_print_light(t_light *light);
void		ft_vec_mat_mlt(t_coords *c, t_matrix *m);
void		ft_swap_double(double *a, double *b);
void		ft_shade(t_surf_pt *p_hit, t_object *obj, t_light *light);
void		ft_shade_sphere(t_surf_pt *p_hit, t_object *obj, t_light *light);
void		ft_shade_flatsurf(t_surf_pt *p_hit, t_object *obj, t_light *light);
void		ft_shade_cylinder(t_surf_pt *p_hit, t_object *obj, t_light *light);
void		ft_shade_color(t_surf_pt *p_hit, int color, t_light *light, double facing_ratio);
void		ft_shade_amblight(t_surf_pt *p_hit, t_object *obj, t_light *amblight);
void		ft_mkscene(t_scene *scene);
void		ft_selectcam(t_scene *scene, int camselect);
void		ft_clear_images(t_scene *scene);
// void		ft_shadray(t_ray *ray, t_scene *scene, t_surf_pt *p_hit);

#endif
