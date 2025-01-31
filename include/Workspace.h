#include "wlr.h"

struct Workspace {
    struct wl_list link;
    struct Output *output;
    struct wl_list toplevels;
    struct Toplevel *active_toplevel;

    Workspace(struct Output *output);
    ~Workspace();

    void add_toplevel(struct Toplevel *toplevel);
    bool contains(struct Toplevel *toplevel);
    bool move_to(struct Toplevel *toplevel, struct Workspace *workspace);
    struct Toplevel *get_toplevel(uint32_t n);
    bool move_to(uint32_t n, struct Workspace *workspace);
    void set_hidden(bool hidden);
    void focus();
    void focus_next();
    void focus_prev();
    void tile();
};
