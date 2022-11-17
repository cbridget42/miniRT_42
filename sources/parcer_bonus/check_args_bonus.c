/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:53:56 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/26 19:52:16 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_info(t_minirt	*info, char	*str)
{
	if (!ft_strncmp(str, "A ", 2) && !info->info_error)
		fill_ambient(info, str);
	else if (!ft_strncmp(str, "C ", 2) && !info->info_error)
		fill_camera(info, str);
	else if (!ft_strncmp(str, "L ", 2) && !info->info_error)
		fill_light(info, str);
	else if (!ft_strncmp(str, "sp ", 3) && !info->info_error)
		fill_sphere(info, str);
	else if (!ft_strncmp(str, "pl ", 3) && !info->info_error)
		fill_plane(info, str);
	else if (!ft_strncmp(str, "cy ", 3) && !info->info_error)
		fill_cylinder(info, str);
	else
		return (5);
	return (info->info_error);
}

static int	read_info(t_minirt	*info, int fd)
{
	char	*str;
	int		ret;

	str = NULL;
	while (1)
	{
		ret = get_next_line(&str, fd);
		if (ret == 1)
			continue ;
		else if (ret == 2)
			break ;
		else if (ret == 4)
			return (ret);
		if (!str)
			break ;
		ret = check_info(info, str);
		if (info->str_arr && ft_strlen(str) != 1 && ret != 5)
			free_str_arr(info->str_arr);
		free(str);
		if (ret)
			return (ret);
		info->info_error = 0;
	}
	return (0);
}

static void	check_to_null(t_minirt	*info)
{
	info->check.l_a = 0;
	info->check.l_p = 0;
	info->check.cam = 0;
	info->check.sph = 0;
	info->check.pln = 0;
	info->check.cyl = 0;
	info->info_error = 0;
	info->light_p = NULL;
	info->scene.spheres = NULL;
	info->scene.planes = NULL;
	info->scene.cylinders = NULL;
}

static void	check_min_max(t_minirt	*info, int	*ret)
{
	if (info->check.l_a != 1 || info->check.l_p < 1 || info->check.cam != 1)
		*ret = 4;
}

int	check_scene(t_minirt	*info, char	*scene)
{
	int	ret;
	int	fd;

	check_to_null(info);
	if (ft_strn_ncmp(scene, ".rt", ft_strlen(scene) - 3, ft_strlen(scene)))
	{
		printf("Invalid argument: wrong filename extension\n");
		return (2);
	}
	fd = open(scene, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return (3);
	}
	ret = read_info(info, fd);
	if (!ret)
		check_min_max(info, &ret);
	close(fd);
	return (ret);
}
