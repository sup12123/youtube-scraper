#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

GtkWidget *text_view;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, ptr, size * nmemb);
    return size * nmemb;
}

void on_button_clicked(GtkButton *button, gpointer user_data) {
    CURL *curl = curl_easy_init();
    if (curl) {
        const gchar *video_url = gtk_entry_get_text(GTK_ENTRY(user_data));

        // Create the URL for the YouTube video page
        char url[256];
        sprintf(url, "https://www.youtube.com/oembed?url=%s&format=json", video_url);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "YouTube Video Scraper");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *url_label = gtk_label_new("YouTube Video URL:");
    gtk_grid_attach(GTK_GRID(grid), url_label, 0, 0, 1, 1);

    GtkWidget *url_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), url_entry, 1, 0, 1, 1);

    GtkWidget *button = gtk_button_new_with_label("Get Video Info");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), url_entry);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_grid_attach(GTK_GRID(grid), text_view, 0, 2, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.youtube_scraper", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
