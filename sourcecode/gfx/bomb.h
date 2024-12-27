#ifndef bomb_include_file
#define bomb_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define bomb_width 7
#define bomb_height 7
#define bomb_size 51
#define bomb ((gfx_sprite_t*)bomb_data)
extern unsigned char bomb_data[51];

#ifdef __cplusplus
}
#endif

#endif
