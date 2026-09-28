// T3SDK Launcher: finds the game, Godot and the T3SDK tools, and runs the
// tools for the user (install the SDK, export maps to Godot, repack edited
// maps). The UI lives in ../src; this side owns every file and process
// operation and exposes them as commands.
mod config;
mod detect;
mod diag;
mod game;
mod ini;
mod proc;
mod saves;
mod tasks;

use std::sync::Mutex;

use tauri::Manager;

pub struct AppState {
    pub config: Mutex<config::Config>,
    pub tasks: tasks::Tasks,
}

pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_dialog::init())
        .plugin(tauri_plugin_opener::init())
        .setup(|app| {
            let config = config::load(app.handle());
            app.manage(AppState { config: Mutex::new(config), tasks: tasks::Tasks::default() });
            Ok(())
        })
        .invoke_handler(tauri::generate_handler![
            config::get_config,
            config::save_config,
            detect::detect_all,
            detect::check_game,
            detect::check_godot,
            detect::check_python,
            detect::check_sdk_root,
            game::overview,
            game::list_maps,
            game::list_mods,
            game::set_mod_enabled,
            game::read_sdk_settings,
            game::write_sdk_settings,
            game::create_sdk_settings,
            game::read_sdk_log,
            game::launch_game,
            game::open_godot,
            game::open_location,
            game::open_link,
            tasks::start_task,
            tasks::cancel_task,
            saves::saves_info,
            saves::list_save_backups,
            saves::create_save_backup,
            saves::restore_save_backup,
            saves::delete_save_backup,
            saves::open_saves_folder,
            diag::collect_logs,
        ])
        .run(tauri::generate_context!())
        .expect("the launcher failed to start");
}
