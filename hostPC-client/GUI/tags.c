static void
create_tags (GtkTextBuffer *buffer)
{
  //GdkBitmap *stipple;

  /* Create a bunch of tags. Note that it's also possible to
   * create tags with gtk_text_tag_new() then add them to the
   * tag table for the buffer, gtk_text_buffer_create_tag() is
   * just a convenience function. Also note that you don't have
   * to give tags a name; pass NULL for the name to create an
   * anonymous tag.
   *
   * In any real app, another useful optimization would be to create
   * a GtkTextTagTable in advance, and reuse the same tag table for
   * all the buffers with the same tag set, instead of creating
   * new copies of the same tags for every buffer.
   *
   * Tags are assigned default priorities in order of addition to the
   * tag table.	 That is, tags created later that affect the same text
   * property affected by an earlier tag will override the earlier
   * tag.  You can modify tag priorities with
   * gtk_text_tag_set_priority().
   */

  gtk_text_buffer_create_tag (buffer, "heading",
			      "weight", PANGO_WEIGHT_BOLD,
			      "size", 15 * PANGO_SCALE,
			      NULL);
  gtk_text_buffer_create_tag(buffer, "white_fg","foreground", "white", NULL);
  gtk_text_buffer_create_tag (buffer, "italic",
			      "style", PANGO_STYLE_ITALIC, NULL);

  gtk_text_buffer_create_tag (buffer, "bold",
			      "weight", PANGO_WEIGHT_BOLD, NULL);  
  
  gtk_text_buffer_create_tag (buffer, "big",
			      /* points times the PANGO_SCALE factor */
			      "size", 20 * PANGO_SCALE, NULL);

  gtk_text_buffer_create_tag (buffer, "xx-small",
			      "scale", PANGO_SCALE_XX_SMALL, NULL);

  gtk_text_buffer_create_tag (buffer, "x-large",
			      "scale", PANGO_SCALE_X_LARGE, NULL);
  
  gtk_text_buffer_create_tag (buffer, "monospace",
			      "family", "monospace", NULL);
  
  gtk_text_buffer_create_tag (buffer, "blue_foreground",
			      "foreground", "blue", NULL);  

  gtk_text_buffer_create_tag (buffer, "red_background",
			      "background", "red", NULL);

  
  gtk_text_buffer_create_tag (buffer, "big_gap_before_line",
			      "pixels_above_lines", 30, NULL);

  gtk_text_buffer_create_tag (buffer, "big_gap_after_line",
			      "pixels_below_lines", 30, NULL);

  gtk_text_buffer_create_tag (buffer, "double_spaced_line",
			      "pixels_inside_wrap", 10, NULL);

  gtk_text_buffer_create_tag (buffer, "not_editable",
			      "editable", FALSE, NULL);
  
  gtk_text_buffer_create_tag (buffer, "word_wrap",
			      "wrap_mode", GTK_WRAP_WORD, NULL);

  gtk_text_buffer_create_tag (buffer, "char_wrap",
			      "wrap_mode", GTK_WRAP_CHAR, NULL);

  gtk_text_buffer_create_tag (buffer, "no_wrap",
			      "wrap_mode", GTK_WRAP_NONE, NULL);
  
  gtk_text_buffer_create_tag (buffer, "center",
			      "justification", GTK_JUSTIFY_CENTER, NULL);

  gtk_text_buffer_create_tag (buffer, "right_justify",
			      "justification", GTK_JUSTIFY_RIGHT, NULL);

  gtk_text_buffer_create_tag (buffer, "wide_margins",
			      "left_margin", 50, "right_margin", 50,
			      NULL);
  
  gtk_text_buffer_create_tag (buffer, "strikethrough",
			      "strikethrough", TRUE, NULL);
  
  gtk_text_buffer_create_tag (buffer, "underline",
			      "underline", PANGO_UNDERLINE_SINGLE, NULL);

  gtk_text_buffer_create_tag (buffer, "double_underline",
			      "underline", PANGO_UNDERLINE_DOUBLE, NULL);

  gtk_text_buffer_create_tag (buffer, "superscript",
			      "rise", 10 * PANGO_SCALE,	  /* 10 pixels */
			      "size", 8 * PANGO_SCALE,	  /* 8 points */
			      NULL);
  
  gtk_text_buffer_create_tag (buffer, "subscript",
			      "rise", -10 * PANGO_SCALE,   /* 10 pixels */
			      "size", 8 * PANGO_SCALE,	   /* 8 points */
			      NULL);

  gtk_text_buffer_create_tag (buffer, "rtl_quote",
			      "wrap_mode", GTK_WRAP_WORD,
			      "direction", GTK_TEXT_DIR_RTL,
			      "indent", 30,
			      "left_margin", 20,
			      "right_margin", 20,
			      NULL);
}
