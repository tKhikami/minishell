#include "header.h"

char    *get_one_argument(char  **str, int c)
{
        int     i;
        char    *ret;

        i = 0;
        if (*str == NULL)
                return (NULL);
        if ((*str)[0] == '\0')
                return (NULL);
        if (c == '\'' || c == '\"')
        {
                i = 1;
                while ((*str)[i] != c && (*str)[i] != '\0')
                        i++;
                ret = ft_substr(*str, 0, i + 1);
                if ((*str)[i] == c)
                        i += 1;
        }
        else
        {
                while ((*str)[i] != '\'' && (*str)[i] != '\"' && (*str)[i] != '\0')
                        i++;
                ret = ft_substr(*str, 0, i);
        }
        *str = *str + i;
        return(ret);
}

char    **divise_argument(char  *str)
{
        char    *ptr;
        char    *tmp;
        t_list  *lst;
        char    **tab;

        if (str == NULL)
                return (NULL);
        ptr = str;
        lst = NULL;
        while (ptr[0] != '\0')
        {
                tmp = get_one_argument(&ptr, ptr[0]);
                if (tmp == NULL)
                {
                        ft_lstclear(&lst, free);
                        return (NULL);
                }
                ft_lstadd_front(&lst, ft_lstnew(tmp));
        }
        tab = ft_lsttotab(lst);
        invert_tab(&tab);
        ft_lstfree(&lst);
        return (tab);
}
