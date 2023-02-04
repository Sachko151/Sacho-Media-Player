#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <stdlib.h>
#include <vlc/vlc.h>
//Declare the global variables
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *lbl_media_name;
GtkWidget *btnStop;
GtkWidget *btnPause;
GtkWidget *btnPlay;
GtkWidget *btnLoad;
GtkWidget *lblProgress;
GtkBuilder *builder;
libvlc_instance_t *inst;
libvlc_media_player_t *mp;
libvlc_media_t *file;
void init_the_gui(int argc, char **argv);
void init_the_media_player(libvlc_media_t *file);
int main(int argc, char **argv){
    init_the_gui(argc, argv);
    return 0;
}
void init_the_gui(int argc, char **argv){
    init_the_media_player(NULL);
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("gui.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    lbl_media_name = GTK_WIDGET(gtk_builder_get_object(builder, "lblMediaName"));
    btnStop = GTK_WIDGET(gtk_builder_get_object(builder, "btnStop"));
    btnPause = GTK_WIDGET(gtk_builder_get_object(builder, "btnPause"));
    btnPlay = GTK_WIDGET(gtk_builder_get_object(builder, "btnPlay"));
    btnLoad = GTK_WIDGET(gtk_builder_get_object(builder, "btnPLoad"));
    lblProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblProgress"));
    gtk_widget_show(window);
    gtk_main();
}
void init_the_media_player(libvlc_media_t *file){
    inst = libvlc_new(0, NULL);
    if(file == NULL){
        printf("%s", "File is empty!");
        return;
    }
    mp = libvlc_media_player_new_from_media(file);
    libvlc_media_release(file);
}
void on_btnPlay_clicked(GtkButton *button){
    if(mp == NULL){
        printf("%s", "not loaded!");
        return;
    }
    printf("%s", "Playing music\n");
    libvlc_media_player_play(mp);
}
void on_btnPause_clicked(GtkButton *button){
    if(mp == NULL){
        printf("%s", "not loaded!");
        return;
    }
    libvlc_media_player_pause(mp);
}
void on_btnStop_clicked(GtkButton *button){
    if(mp == NULL){
        printf("%s", "not loaded!\n");
        return;
    }
    printf("%s", "Music is stopped\n");
    libvlc_media_player_stop(mp);
}
void on_btnLoad_clicked(GtkButton *button){
    printf("%s", "Loading File\n");
    file = libvlc_media_new_path(inst, "/home/sachko/Music/Background Music/Cipher.mp3");
    init_the_media_player(file);
    gtk_label_set_text(GTK_LABEL(lbl_media_name), (gchar*) "Cipher.mp3");
}