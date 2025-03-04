#include "Server.h"

Popup::Popup(wlr_xdg_popup *xdg_popup, wlr_scene_tree* parent_tree, Server *server)
        : server(server),
        xdg_popup(xdg_popup),
        parent_tree(wlr_scene_xdg_surface_create(parent_tree, xdg_popup->base)){
        xdg_popup->base->data = parent_tree;

    // xdg_popup_commit
    commit.notify = [](wl_listener *listener, [[maybe_unused]] void *data) {
        Popup *popup = wl_container_of(listener, popup, commit);
        Output *output = popup->server->focused_output();

        if (!output)
            return;

        int lx, ly;
        wlr_scene_node_coords(&popup->parent_tree->node.parent->node, &lx, &ly);

        wlr_box box = {
            .x = output->usable_area.x - lx,
            .y = output->usable_area.y - ly,
            .width = output->usable_area.width,
            .height = output->usable_area.height,
        };

        wlr_xdg_popup_unconstrain_from_box(popup->xdg_popup, &box);

        if(popup->xdg_popup->base->initial_commit)
            wlr_xdg_surface_schedule_configure(popup->xdg_popup->base);
    };
    wl_signal_add(&xdg_popup->base->surface->events.commit, &commit);

    // xdg_popup_destroy
    destroy.notify = [](wl_listener *listener, [[maybe_unused]] void *data) {
        Popup *popup = wl_container_of(listener, popup, destroy);
        delete popup;
    };
    wl_signal_add(&xdg_popup->events.destroy, &destroy);
}

Popup::~Popup() {
    wl_list_remove(&commit.link);
    wl_list_remove(&destroy.link);
}
