/** @file gttk_Spinbox.cpp
 * Copyright (c) 2020 RedFantom
 *
 * Widget layout: TSpinbox
 * - Spinbox.field
 * - Spinbox.buttons
 * |- Spinbox.uparrow
 * |- Spinbox.downarrow
 * - Spinbox.padding
 */
#include "gttk_Utilities.h"
#include "gttk_TkHeaders.h"
#include "gttk_WidgetDefaults.h"

static void spinbox_field_geometry(
    void* clientData, void* elementRecord, Tk_Window tkwin,
    int* widthPtr, int* heightPtr, Ttk_Padding* paddingPtr) {
  GTTK_WIDGET_CACHE_DEFINITION
  GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE
  GtkWidget* widget = gttk_get_spin_button(wc);
  GTTK_ENSURE_WIDGET_OK
  *paddingPtr = Ttk_UniformPadding(10);
}


static void spinbox_field_draw(
    void* clientData, void* elementRecord, Tk_Window tkwin, Drawable d, Ttk_Box b, unsigned state) {
  GTTK_GTK_DRAWABLE_DEFINITIONS
  GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE
  GtkWidget* widget = gttk_get_spin_button(wc);

  GTTK_ENSURE_WIDGET_OK

  GTTK_DRAWABLE_FROM_WIDGET
  GTTK_STYLE_FROM_WIDGET

  gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin, 0, 0, b.width, b.height, b.x, b.y);
  GTTK_CLEANUP_GTK_DRAWABLE
}


// Element: Spinbox.field
struct SpinboxField {};

static Ttk_ElementOptionSpec spinbox_field_options[] = {
    {nullptr}
}; // spinbox_field_options

static Ttk_ElementSpec spinbox_field_spec = {
  TK_STYLE_VERSION_2,
  sizeof(struct SpinboxField),
  spinbox_field_options,
  spinbox_field_geometry,
  spinbox_field_draw
}; // spinbox_field_spec

// Element: Spinbox.buttons
struct SpinboxButtons {};

static Ttk_ElementSpec spinbox_buttons_spec = {

}; // spinbox_buttons_spec

// Element: Spinbox.uparrow
struct SpinboxUparrow {};

static Ttk_ElementSpec spinbox_uparrow_spec = {

};

// Element: Spinbox.downarrow
struct SpinboxDownarrow {};

static Ttk_ElementSpec spinbox_downarrow_spec = {
    TK_STYLE_VERSION_2,
    sizeof(struct SpinboxDownarrow),

};

TTK_BEGIN_LAYOUT(SpinboxLayout)
  TTK_NODE("Spinbox.field", TTK_SIDE_TOP | TTK_STICK_W | TTK_STICK_E | TTK_FILL_BOTH)
            // TTK_GROUP("Spinbox.buttons", TTK_SIDE_RIGHT,
            //           TTK_NODE("Spinbox.uparrow", TTK_SIDE_RIGHT)
            //           TTK_NODE("Spinbox.downarrow", TTK_SIDE_RIGHT))
  // )
TTK_END_LAYOUT

int gttk_init_spinbox(Tcl_Interp* interp, gttk_WidgetCache** wc, Ttk_Theme theme) {
  /** Initialize Spinbox widget layout and elements */
  Ttk_RegisterElement(interp, theme, "Spinbox.field", &spinbox_field_spec, wc[0]);
  // Ttk_RegisterElement(interp, theme, "Spinbox.buttons", &spinbox_buttons_spec, wc[0]);
  // Ttk_RegisterElement(interp, theme, "Spinbox.uparrow", &spinbox_uparrow_spec, wc[0]);
  // Ttk_RegisterElement(interp, theme, "Spinbox.downarrow", &spinbox_downarrow_spec, wc[0]);

  Ttk_RegisterLayout(theme, "TSpinbox", SpinboxLayout);
  return TCL_OK;
} // gttk_init_spinbox
