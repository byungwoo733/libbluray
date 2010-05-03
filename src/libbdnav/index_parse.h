#if !defined(_INDX_PARSE_H_)
#define _INDX_PARSE_H_

#include <stdio.h>
#include <stdint.h>

typedef enum {
    indx_video_format_ignored,
    indx_video_480i,
    indx_video_576i,
    indx_video_480p,
    indx_video_1080i,
    indx_video_720p,
    indx_video_1080p,
    indx_video_576p,
} indx_video_format;

typedef enum {
    indx_fps_reserved1,
    indx_fps_23_976,
    indx_fps_24,
    indx_fps_25,
    indx_fps_29_97,
    indx_fps_reserved2,
    indx_fps_50,
    indx_fps_59_94,
} indx_frame_rate;

typedef enum {
    indx_object_type_hdmv = 1,
    indx_object_type_bdj  = 2,
} indx_object_type;

typedef enum {
    indx_hdmv_playback_type_movie       = 0,
    indx_hdmv_playback_type_interactive = 1,
} indx_hdmv_playback_type;

typedef enum {
    indx_bdj_playback_type_movie       = 2,
    indx_bdj_playback_type_interactive = 3,
} indx_bdj_playback_type;

typedef struct {
    uint8_t           initial_output_mode_preference : 1; /* 0 - 2D, 1 - 3D */
    uint8_t           content_exist_flag : 1;
    indx_video_format video_format;
    indx_frame_rate   frame_rate;
    uint8_t           user_data[32];
} INDX_APP_INFO;

typedef struct {
    indx_bdj_playback_type playback_type;
    uint8_t                name[6];
} INDX_BDJ_OBJ;

typedef struct {
    indx_hdmv_playback_type playback_type;
    uint16_t                id_ref;
} INDX_HDMV_OBJ;

typedef struct {
    indx_object_type   object_type;
    union {
        INDX_BDJ_OBJ   bdj;
        INDX_HDMV_OBJ  hdmv;
    };
} INDX_PLAY_ITEM;

typedef struct {
    indx_object_type   object_type;
    uint8_t            access_type : 2;
    union {
        INDX_BDJ_OBJ   bdj;
        INDX_HDMV_OBJ  hdmv;
    };
} INDX_TITLE;

typedef struct indx_root_s {
    INDX_APP_INFO  app_info;
    INDX_PLAY_ITEM first_play;
    INDX_PLAY_ITEM top_menu;

    uint16_t       num_titles;
    INDX_TITLE    *titles;
} INDX_ROOT;


INDX_ROOT* indx_parse(const char *path); /* parse index.bdmv */
void indx_free(INDX_ROOT *index);

#endif // _INDX_PARSE_H_

