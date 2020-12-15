/*
 *  gttk_Menubutton.cpp
 * -------------------
 *
 * This file is part of the gttk package, a Tk/Tile based theme that uses
 * Gtk/GNOME for drawing.
 *
 * Copyright (C) 2004-2008 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "gttk_Utilities.h"
#include "gttk_TkHeaders.h"
#include "gttk_WidgetDefaults.h"

#if 0
/*
 * Pushbuttons (Tk: "Menubutton")
 */
static Ttk_StateTable menubutton_statemap[] =
{
};
#endif

typedef struct {
} MenubuttonIndicatorElement;

static Ttk_ElementOptionSpec MenubuttonIndicatorElementOptions[] = {
    {NULL}
};

static void MenubuttonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    GTTK_WIDGET_CACHE_DEFINITION;
    gint size = 15;
    GtkWidget *widget = gttk_GetComboboxEntry(wc);
    GTTK_ENSURE_WIDGET_OK;
    gtk_widget_style_get(widget, "arrow-size", &size, NULL);

    *widthPtr = *heightPtr = size;
    *paddingPtr = Ttk_UniformPadding(3);
}

static void MenubuttonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    GTTK_GTK_DRAWABLE_DEFINITIONS;
    GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    /* GTTK_SETUP_GTK_DRAWABLE; */
    GtkWidget *widget = gttk_GetCombobox(wc);
    GtkWidget *arrow_widget = gttk_GetArrow(wc);
    gfloat arrow_scaling;
    gint arrow_x;
    gint arrow_y;
    gint arrow_width;
    gint arrow_height;
    GTTK_ENSURE_WIDGET_OK;
    GTTK_STYLE_FROM_WIDGET;
    GTTK_DRAWABLE_FROM_WIDGET;
    gttk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            GTTK_SECTION_BUTTONS|GTTK_SECTION_ALL);
    GTTK_WIDGET_SET_FOCUS(widget);
    gtk_paint_flat_box(style, gdkDrawable, gtkState, gtkShadow, NULL, widget,
            "button", 0, 0, b.width, b.height);
    /* Draw the arrow, according to the desired scaling! */
    gtk_widget_style_get(arrow_widget, "arrow-scaling",
                                 &arrow_scaling, NULL);
    if (arrow_scaling == 0.0) arrow_scaling = 1.0;
    arrow_width  = b.width  * arrow_scaling;
    arrow_height = b.height * arrow_scaling;
    arrow_x =  (b.width  - arrow_width) / 2;
    arrow_y =  (b.height - arrow_height) / 2;
    gtk_paint_arrow(style, gdkDrawable, gtkState, gtkShadow, NULL,
        arrow_widget, "combo", GTK_ARROW_DOWN, TRUE,
        arrow_x, arrow_y, arrow_width, arrow_height);
    gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    GTTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec MenubuttonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonIndicatorElement),
    MenubuttonIndicatorElementOptions,
    MenubuttonIndicatorElementGeometry,
    MenubuttonIndicatorElementDraw
};

typedef struct {
} MenubuttonElement;

static Ttk_ElementOptionSpec MenubuttonElementOptions[] = {
    {NULL}
};

static void MenubuttonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    GTTK_WIDGET_CACHE_DEFINITION;
    GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = gttk_GetCombobox(wc);
    GTTK_ENSURE_WIDGET_OK;
    GTTK_GET_WIDGET_SIZE(*widthPtr, *heightPtr);
    *paddingPtr = Ttk_UniformPadding(PushButtonUniformPadding);
}

static void MenubuttonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    GTTK_GTK_DRAWABLE_DEFINITIONS;
    GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    /* GTTK_SETUP_GTK_DRAWABLE; */
    GtkWidget *widget = gttk_GetCombobox(wc);
    GTTK_ENSURE_WIDGET_OK;
    GTTK_DRAWABLE_FROM_WIDGET;
    GTTK_STYLE_BACKGROUND_DEFAULT;
    GTTK_DEFAULT_BACKGROUND;
    GTTK_STYLE_FROM_WIDGET;
    gttk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            GTTK_SECTION_BUTTONS|GTTK_SECTION_ALL);
    GTTK_WIDGET_SET_FOCUS(widget);
    gtk_paint_box(style, gdkDrawable, gtkState, gtkShadow, NULL, widget,
                  "button", 0, 0, b.width, b.height);
    gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin,
                  0, 0, b.width, b.height, b.x, b.y);
    GTTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec MenubuttonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonElement),
    MenubuttonElementOptions,
    MenubuttonElementGeometry,
    MenubuttonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(MenubuttonLayout)
    TTK_GROUP("Menubutton.border", TTK_FILL_BOTH,
	TTK_GROUP("Menubutton.focus", TTK_FILL_BOTH,
	    TTK_NODE("Menubutton.indicator", TTK_PACK_RIGHT)
	    TTK_GROUP("Menubutton.padding", TTK_PACK_LEFT|TTK_EXPAND|TTK_FILL_X,
	        TTK_NODE("Menubutton.label", TTK_PACK_LEFT))))
TTK_END_LAYOUT

int gttk_Init_Menubutton(Tcl_Interp *interp,
                       gttk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Menubutton.indicator",
            &MenubuttonIndicatorElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Menubutton.border",
            &MenubuttonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* gttk_Init_Menubutton */
