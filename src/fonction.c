size_t      ft_lstlen(t_lst *lst)
{
      size_t      i;

      i = 0;
      while (lst != NULL)
      {
            i++;
            lst = lst->next;
      }
      return (i);
}

struct stat {
    mode_t    st_mode;     /* Protection */
    nlink_t   st_nlink;    /* Nb liens matériels */
    uid_t     st_uid;      /* UID propriétaire */
    gid_t     st_gid;      /* GID propriétaire */
    blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
    time_t    st_mtime;    /* Heure dernière modification */
    time_t    st_ctime;    /* Heure dernier changement état */
};
