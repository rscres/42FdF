void draw_line(t_matrix start, t_matrix end, t_img *mlx_img)
{
    if (abs(end.y - start.y) < abs(end.x - start.x))
    {
        if (start.x > end.x)
            steep_line(end, start, mlx_img);
        else
            steep_line(start, end, mlx_img);
    }
    else
    {
        if (start.y > end.y)
            vertical_line(end, start, mlx_img);
        else
            vertical_line(start, end, mlx_img);
    }
}

void vertical_line(t_matrix start, t_matrix end, t_img *mlx_img)
{
    t_matrix temp;
    int y;

    if (start.y > end.y)
    {
        temp = start;
        start = end;
        end = temp;
    }
    y = start.y;
    while (y < end.y)
    {
        my_mlx_pixel_put(mlx_img, start.x, y, interpolate_color(start, end, y));
        y++;
    }
    my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
}

t_color interpolate_color(t_matrix start, t_matrix end, int current_y)
{
    double percent = (double)(current_y - start.y) / (double)(end.y - start.y);
    t_color result;

    result.r = (int)((start.color >> 16 & 0xff) * (1 - percent) + (end.color >> 16 & 0xff) * percent);
    result.g = (int)((start.color >> 8 & 0xff) * (1 - percent) + (end.color >> 8 & 0xff) * percent);
    result.b = (int)((start.color & 0xff) * (1 - percent) + (end.color & 0xff) * percent);
    result.a = (int)((start.color >> 24 & 0xff) * (1 - percent) + (end.color >> 24 & 0xff) * percent);
    return (result);
}

void my_mlx_pixel_put(t_img *img, int x, int y, t_color color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}