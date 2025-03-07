#include "wlr.h"

struct OutputManager {
    Server *server;

    wl_list outputs;
    wlr_output_layout *layout;

    wlr_xdg_output_manager_v1 *wlr_xdg_output_manager;
    wlr_output_manager_v1 *wlr_output_manager;
    wl_listener apply;
    wl_listener test;
    wl_listener destroy;
    wl_listener new_output;
    wl_listener change;

    OutputManager(Server *server);
    ~OutputManager();

    void apply_config(wlr_output_configuration_v1 *cfg, bool test_only) const;

    Output *get_output(const wlr_output *wlr_output);
    Output *output_at(double x, double y);

    void arrange() const;
};
