#include"cub3D.h"


int get_door_frame(t_doorlist *tmp,t_data *data)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
    {
        if(data->map.doors[i].x == (int)tmp->doorhitx && data->map.doors[i].y == (int)tmp->doorhity)
            return (data->map.doors[i].frame);
        i++;
    }
    return (0);
}

int door_state(t_data *data, int x, int y)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
    {
        if(data->map.doors[i].x == x && data->map.doors[i].y == y)
        {
            return (data->map.doors[i].state);
        }
        i++;
    }
    return (0);
}


void door_textures(t_data *data)
{
    mlx_texture_t *texture;
    int i;
    char *path;

    i = 0;
    data->texture.door = malloc(sizeof(mlx_image_t*) * 35);
    path = ft_strdup("textures/door/frame-000.png");
    while(i < 35)
    {
        path[21] = (i+1) / 10 + '0';
        path[22] = (i+1) % 10 + '0';
        texture = mlx_load_png(path);
        if(!texture)
            exit(1);
        data->texture.door[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->texture.door[i] , 250, 250);
        mlx_delete_texture(texture);
        i++;
    }
    free(path);
}

void door_frames_setter(t_data *data)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
    {
       if(data->map.doors[i].state == CLOSED)
            data->map.doors[i].frame = 0;
        else if(data->map.doors[i].state == OPENING)
            data->map.doors[i].frame++;
        else if(data->map.doors[i].state == OPENED)
            data->map.doors[i].frame = 34;
        else if(data->map.doors[i].state == CLOSING)
            data->map.doors[i].frame--;
        if (data->map.doors[i].frame <= 0)
        {
            data->map.doors[i].frame = 0;
            data->map.doors[i].state = CLOSED;
        }
        if (data->map.doors[i].frame > 34)
        {
            data->map.doors[i].frame = 34;
            data->map.doors[i].state = OPENED;
        }
        i++;
    }
}

void free_door_list(t_data *data)
{
    t_doorlist *tmp;
    t_doorlist *tmp2;

    tmp = data->ray.doorlist;
    if(!tmp)
        return;
    while (tmp != NULL)
    {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    data->ray.doorlist = NULL;
}

void door_remote(t_data *data, int i,t_doorlist *tmp)
{
    if (data->map.doors[i].x == (int)tmp->doorhitx && data->map.doors[i].y == (int)tmp->doorhity && tmp->doordistance < 3 && tmp->doordistance > 0.15)
       {
        if (data->map.doors[i].state == OPENING)
            data->map.doors[i].state = CLOSING;
       else if (data->map.doors[i].state == CLOSING)
            data->map.doors[i].state = OPENING;
        else if (data->map.doors[i].state == CLOSED)
            data->map.doors[i].state = OPENING;
        else if (data->map.doors[i].state == OPENED)
            data->map.doors[i].state = CLOSING;
        }
}

void door_frames_controller(t_data *data)
{
    t_doorlist *tmp;
    int i = 0;

    hits(data->player.angle,data);
    tmp = data->ray.doorlist;
    if (tmp)
        while(tmp->next)
            tmp = tmp->next;
    if(!tmp)
    {
        free_door_list(data);
        return;
    }
    if (tmp)
    {
        while(i < data->map.doors_count)
            {
                door_remote(data, i,tmp);
                i++;
            }
    }
    free_door_list(data);
}

void add_back_to_doors(t_data *data, double x, double y,int side)
{
    t_doorlist *new;
    t_doorlist *last;

    new = malloc(sizeof(t_doorlist));
    new->doorhitx = x;
    new->doorhity = y;
    new->doorhitside = side;
    new->doordistance = sqrtf(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));
    new->next = NULL;
    if (data->ray.doorlist == NULL)
    {
        data->ray.doorlist = new;
        return;
    }
    last = data->ray.doorlist;
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}

static void swap(t_doorlist *a, t_doorlist *b)
{
    t_doorlist tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_door_list(t_data *data)
{
    t_doorlist *prev;
    t_doorlist *current;
    t_doorlist *next;

    prev = NULL;
    current = data->ray.doorlist;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next; 
    }
    data->ray.doorlist = prev;
}


size_t door_list_size(t_doorlist *head)
{
    size_t size;
    t_doorlist *tmp;

    size = 0;
    tmp = head;
    while(tmp)
    {
        size++;
        tmp = tmp->next;
    }
    return (size);
}
void array_bubble_sort(t_doorlist **arr, size_t size)
{
    int j;
    int k;

    j = 0;
    while (j < size-1)
    {
        k = 0;
        while (k < size-j-1)
        {
            if (arr[k]->doordistance > arr[k+1]->doordistance)
                swap(arr[k], arr[k+1]);
            k++;
        }
        j++;
    }
}

void rebuild_door_list(t_data *data, t_doorlist **arr, size_t size)
{
    size_t i;
    
    i = 0;
    data->ray.doorlist = arr[0];
    while(i < size - 1)
    {
        arr[i]->next = arr[i+1];
        i++;
    }
    arr[i]->next = NULL;
}


void sort_door_list(t_data *data, int reverse)
{
    t_doorlist *tmp;
    t_doorlist **arr;
    size_t size;
    size_t i;

    size = door_list_size(data->ray.doorlist);
    if (size <= 1)
        return;
    arr = malloc(sizeof(t_doorlist*) * size);
    tmp = data->ray.doorlist;
    i = 0;
    while(tmp)
    {
        arr[i] = tmp;
        tmp = tmp->next;
        i++;
    }
    array_bubble_sort(arr, size);
    rebuild_door_list(data, arr, size);
    if (reverse)
        reverse_door_list(data);
    free(arr);
}

