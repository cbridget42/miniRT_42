/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:16:11 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 18:15:43 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "minirt.h"

void	select_obj_x(t_minirt *data, char sign);
void	select_obj_y(t_minirt *data, char sign);
void	select_obj_z(t_minirt *data, char sign);
void	conf_axis(t_minirt *data, float *axis, char sign);
void	change_review(t_minirt *data);

void	change_obj(t_minirt *data);
void	change_sphere(t_minirt *data, void **obj_tmp, int *i);
void	change_plane(t_minirt *data, void **obj_tmp, int *i);
void	change_cylinder(t_minirt *data, void **obj_tmp, int *i);
void	change_light(t_minirt *data, void **obj_tmp, int *i);

void	rerender(t_minirt *data, int flag);

#endif
