#include <gtk/gtk.h>
#include <curl/curl.h>

GtkWidget *url_entry;
GtkWidget *response_text_view;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Append the response to the text view
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(response_text_view));
    gtk_text_buffer_insert_at_cursor(buffer, ptr, -1);
    return size * nmemb;
}

void send_request(GtkButton *button, gpointer data) {
    const gchar *url = gtk_entry_get_text(GTK_ENTRY(url_entry));

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    url_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), url_entry, FALSE, FALSE, 0);

    GtkWidget *send_button = gtk_button_new_with_label("Send Request");
    g_signal_connect(send_button, "clicked", G_CALLBACK(send_request), NULL);
    gtk_box_pack_start(GTK_BOX(box), send_button, FALSE, FALSE, 0);

    response_text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(box), response_text_view, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
