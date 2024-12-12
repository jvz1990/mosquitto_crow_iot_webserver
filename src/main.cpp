#include <csignal>
#include <fmt/core.h>

#include "app.h"

crowiot::App app;

void signalHandler(int signal) {
  app.stopServices();
  std::exit(signal);
}

void setupSignalHandlers() {
  struct sigaction sa;
  sa.sa_handler = signalHandler;
  sa.sa_flags = SA_RESTART | SA_SIGINFO;
  sigemptyset(&sa.sa_mask);

  int signals[] = {SIGHUP,  SIGINT,  SIGQUIT, SIGILL,    SIGABRT, SIGFPE,
                   SIGSEGV, SIGPIPE, SIGALRM, SIGTERM,   SIGUSR1, SIGUSR2,
                   SIGCHLD, SIGCONT, SIGTSTP, SIGTTIN,   SIGTTOU, SIGBUS,
                   SIGPOLL, SIGPROF, SIGSYS,  SIGTRAP,   SIGURG,  SIGVTALRM,
                   SIGXCPU, SIGXFSZ, SIGIOT,  SIGSTKFLT, SIGIO,   SIGPWR};

  for (int sig : signals) {
    sigaction(sig, &sa, nullptr);
  }
}

int main() {
  app.startServices();

  std::this_thread::sleep_for(std::chrono::seconds(5));

  setupSignalHandlers();

  while (app.isAppRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  app.stopServices();

  return 0;
}
