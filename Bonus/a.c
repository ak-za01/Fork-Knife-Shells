/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/10 01:45:00 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int count_files(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(path);
    if (!dir)
        return (0);
    while ((entry = readdir(dir)))
    {
            count++;
    }
    closedir(dir);
    return (count);
}

// Allocate and fill new c_arg with matched files
static char **build_arg_list(const char *path, int count)
{
    DIR *dir;
    struct dirent *entry;
    char **new_args;
    int i = 0;

    new_args = malloc((count + 2) * sizeof(char *)); // +1 for cmd, +1 for NULL
    if (!new_args)
        return (NULL);

	dir = opendir(path);
    if (!dir)
    {
        free(new_args[0]);
        free(new_args);
        return (NULL);
    }
	
    while ((entry = readdir(dir)))
    {
		struct stat st;
		char full_path[1024];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
		new_args[++i] = strdup(entry->d_name);
       
    }
    new_args[i + 1] = NULL;
    closedir(dir);
    return (new_args);
}


int ft_get_wc_list_filled(char **t, int s,const  char *cwd)
{
    int i;
	DIR				*dir;
	struct dirent	*key;
    
    i=0;
    dir=opendir(cwd);
    if(!dir)
        return -1;
    while((key = readdir(dir)))
    {
        t[i]=strdup(key->d_name);
        if(!t[i])
		    return (-1);
        i++;
    }
    closedir(dir);
    return 0;
}

int main()
{
    char cwd[1024];
    int file_count;
    char **new_args;

    if (!getcwd(cwd, sizeof(cwd)))
        return 0;

    // file_count = ft_get_wc_list_size(cwd);
    file_count = count_files(cwd);
   printf(">%d<",file_count);


	char **t = malloc((file_count + 1) * sizeof(char *));
	 ft_get_wc_list_filled(t, file_count,cwd);
	//  t=build_arg_list(cwd,file_count );
    printf("Expanded list: \n");
    for (int i = 1; t[i]; i++)
        printf("\t %s \n", t[i]);
    printf("\n");

	return (0);
}


