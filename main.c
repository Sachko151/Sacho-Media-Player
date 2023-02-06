#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <vlc/vlc.h>
#include <stddef.h>
//Declare the global variables
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *lbl_media_name;
GtkWidget *btnStop;
GtkWidget *btnPause;
GtkWidget *btnPlay;
GtkWidget *btnLoad;
GtkWidget *btnFileChooser;
GtkWidget *lblProgress;
GtkBuilder *builder;
libvlc_instance_t *inst;
libvlc_media_player_t *mp;
libvlc_media_t *file;
void init_the_gui(int argc, char **argv);
void init_the_media_player(libvlc_media_t *file);
void logTheProgress(libvlc_media_player_t *mp);
static gboolean print_progress(GtkWidget *progress);
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
    lblProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblProgress"));
    btnStop = GTK_WIDGET(gtk_builder_get_object(builder, "btnStop"));
    btnPause = GTK_WIDGET(gtk_builder_get_object(builder, "btnPause"));
    btnPlay = GTK_WIDGET(gtk_builder_get_object(builder, "btnPlay"));
    btnLoad = GTK_WIDGET(gtk_builder_get_object(builder, "btnPLoad"));
    btnFileChooser = gtk_file_chooser_button_new(("Select a file"),
                                        GTK_FILE_CHOOSER_ACTION_OPEN);
    g_timeout_add(250, G_SOURCE_FUNC(print_progress), GTK_LABEL(lblProgress));
    lblProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblProgress"));
    gtk_widget_show(window);
    gtk_main();
}
void logTheProgress(libvlc_media_player_t *mp){
    int64_t length_in_seconds =  libvlc_media_player_get_length(mp) / 1000;
    printf("Length:%ld", length_in_seconds);
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
        return;
    }
    libvlc_media_player_play(mp);
}
void on_btnPause_clicked(GtkButton *button){
    if(mp == NULL){
        return;
    }
    logTheProgress(mp);
    libvlc_media_player_pause(mp);
}
void on_btnStop_clicked(GtkButton *button){
    if(mp == NULL){
        return;
    }
    libvlc_media_player_stop(mp);
}
void on_btnFileChooser_file_set(GtkFileChooserButton *button, gpointer user_data){
    if(file != NULL){
        libvlc_media_player_stop(mp);
    }
    file = libvlc_media_new_path(inst, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button)));
    init_the_media_player(file);
    printf("%s", "set_file\n");
}
void on_btnFileChooser_selection_changed(GtkFileChooserButton *button){
    printf("%s", "selection_changed\n");
}
static gboolean print_progress(GtkWidget *progress){
    int64_t time_in_seconds;
    if(mp != NULL){
         time_in_seconds = (int64_t)libvlc_media_player_get_time(mp) / 1000;
    }
     time_in_seconds = 0;
    char *text;
    text = g_strdup_printf("%ld", time_in_seconds);
    gtk_label_set_label ( GTK_LABEL ( lblProgress ), text );
    g_free(text);
    return TRUE;
}