// No console window behind the launcher in release builds on Windows.
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

fn main() {
    t3sdk_launcher_lib::run()
}
