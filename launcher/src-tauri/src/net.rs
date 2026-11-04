// HTTPS for the launcher's own downloads (the mod index and its packages, the
// portable update): Windows' own TLS (Schannel) there, the platform's root
// certificates, HTTPS only.
use std::time::Duration;

pub fn agent() -> ureq::Agent {
    use ureq::tls::{RootCerts, TlsConfig, TlsProvider};
    let tls = TlsConfig::builder().provider(TlsProvider::NativeTls).root_certs(RootCerts::PlatformVerifier).build();
    ureq::Agent::config_builder()
        .tls_config(tls)
        .https_only(true)
        .user_agent(format!("T3SDK-Launcher/{}", env!("CARGO_PKG_VERSION")))
        .timeout_connect(Some(Duration::from_secs(20)))
        .timeout_recv_response(Some(Duration::from_secs(30)))
        .build()
        .into()
}
