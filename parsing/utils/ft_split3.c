/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:45:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/09 18:59:40 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

static int ft_check_t(char const *t , char ** c )
{
	int k=0;
	while(c[k])
	{
		if(k<2)
		{
			if((t[0] && t[1]) && (t[0]==c[k][0])&& t[1]==c[k][1])
				return (k);
				// return (printf("!: %d\n",k), k);
		}
		else
		{
			int s=ft_strlen(c[k]);
			if(t[0]==c[k][0])
				return (k);
		}
		k++;
	}
	return -1;
}

static int ft_count(char const *str, char **charset)
{
	int x=0;
	int copy=0;
	int k=0;
	int f=0;
	
	while(str[x])
	{
		k=ft_check_t(str+x, charset);
		if(k == -1 )
		{
			if(f==0)
			{	
				copy++;
				f=1;
				x++;
			}
			else
			{
				x++;
			}
		}
		else
		{
			copy++;
			f=0;
			if(k<2)
			{
				printf("!. x is %c%c  \n",str[x],str[x+1]);
				x+=2;
			}
			else
			{
				printf("?. x is %c \n",str[x]);
				x++;
			}
		}
	}
	return copy;
}

char 	**ft_split3(char const *str)
{
	int		i;
	int		x;
	int		y;
	int 	k;
	int 	f;
	char	**result;
	
	char	**charset = malloc(sizeof(char*)*6);
    charset[0]=">>";
    charset[1]="<<";
    charset[2]=">";
    charset[3]="<";
    charset[4]="|";
    charset[5]= NULL;

	i=0;
	x=0;
	f=0;
	
	int s=ft_count(str, charset);
	char  **t=malloc(sizeof(char*)*(s+1));
	while(i<s)
	{
		t[i]=malloc((sizeof(char) * s));
		y=x;
		while(str[x])
		{
			k=ft_check_t(str+x, charset);
			if(k == -1)
			{
				x++;
			}
			else
			{
				f=0;
				if(k<2)
				{
					// printf("!. x is %c%c  \n",str[x],str[x+1]);
					x+=2;
				}
				else
				{
					// printf("?. x is %c \n",str[x]);
					x++;
				}
			}
		}	
		i++;
	}
	printf("\n& count of worlds is %d &\n", s);

	// print_tab(charset);
	return charset;
}
