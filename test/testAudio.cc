#include "audio/AudioPlayer.hh"
#include "opengl/GrailGUI.hh"

using namespace std;
using namespace grail;

class TestAudioPlayer : public GLWin {
 private:
  double startTime;
  AudioPlayer *a;
  int step;

 public:
  TestAudioPlayer()
      : GLWin(0x000000, 0xCCCCCC, "TestAudioPlayer"),
        startTime(0),
        a(nullptr),
        step(0) {}

  // required to ensure that the memory of the audio player is freed
  ~TestAudioPlayer() { delete a; }

  // using the built in timing of GLWin and if statements allows for control
  // flow of the player with respect to time the program has been running
  void update() {
    double time = getTime();

    if (time > startTime + 1 && step == 0) {
      printf("simultaneous playback\n");
      a->setCurrentContext("default");
      a->setPlaying();
      a->setCurrentContext("new context");
      a->setPlaying();
      startTime = time;
      step++;
    }

    if (time > startTime + 10 && step == 1) {
      printf("play from youtube\n");
      a->setCurrentContext("default");
      a->setPaused();
      a->setCurrentContext("new context");
      a->setPaused();

      a->setCurrentContext("from youtube");
      a->setPlaying();
      startTime = time;
      step++;
    }

    if (time > startTime + 5 && step == 2) {
      printf("skip to 1:52 in song\n");
      a->setCurrentContext("from youtube");
      a->seekLocation("1:52", "absolute");
      a->printCurrentTime();

      // this should fail, chicken not valid lmao
      a->seekLocation("66", "chicken");

      startTime = time;
      step++;
    }

    if (time > startTime + 7 && step == 3) {
      printf("revert skip\n");
      a->setCurrentContext("from youtube");
      a->revertSeek();
      a->printCurrentTime();
      startTime = time;
      step++;
    }

    if (time > startTime + 5 && step == 4) {
      printf("try to play a playlist from youtube\n");
      a->setCurrentContext("from youtube");
      a->setPaused();

      a->setCurrentContext("skyhill");
      a->setPlaying();
      startTime = time;
      step++;
    }

    if (time > startTime + 10 && step == 5) {
      printf("next song in playlist\n");
      a->setCurrentContext("skyhill");
      // skip to next song in playlist
      a->playlistNext();
      startTime = time;
      step++;
    }

    if (time > startTime + 10 && step == 6) {
      printf("go to specific index in playlist\n");
      a->setCurrentContext("skyhill");
      // jump to a specific index in playlist
      a->playlistPlayIndex(6);
      startTime = time;
      step++;
    }

    if (time > startTime + 7 && step == 7) {
      printf("go to prev track in playlist\n");
      a->setCurrentContext("skyhill");
      // go back a track in playlist
      a->playlistPrev();
      startTime = time;
      step++;
    }
  }

  void init() {
    startTime = getTime();
    MainCanvas *c = currentTab()->getMainCanvas();

    StyledMultiShape2D *m = c->getGui();

    a = new AudioPlayer();

    // The initial context created with an AudioPlayer is called default
    // Before performing operations on an mpv context, you have to set the
    // current context of the AudioPlayer object
    a->setCurrentContext("default");
    a->setVolume(50);
    a->addFile("res/sample1mb.ogg");

    // creating a new context, calling it "new context"
    // set the current context to the new one, give it a playlist that mpv can
    // understand (see playlist.txt in test/res/)
    a->newContext("new context");
    a->setCurrentContext("new context");
    a->setVolume(50);
    a->addFile("res/playlist.txt");

    // if you try to set a current context that doesn't exist, a message will
    // print telling you what's happened
    a->setCurrentContext("i should print something");

    // mpv can play things from the internet utilizing youtube-dl, here's an
    // example of how to do it
    a->newContext("from youtube");
    a->setCurrentContext("from youtube");
    a->addFile("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    a->setVolume(50);

    // because of how commands are given to mpv, there's a limit on how long
    // the number for the volume is allowed to be (makes sure a sprintf
    // doesn't write to memory it doesn't have access to). this limit is
    // between 0 and 999
    a->setVolume(11111);

    a->newContext("skyhill");
    a->setCurrentContext("skyhill");
    a->addFile(
        "https://www.youtube.com/"
        "playlist?list=PLcKMZE_1oNKHZ5tN8FPiQNkLVTa-LrMpr");
    a->setVolume(50);
  }
};

int main(int argc, char *argv[]) {
  return GLWin::init(new TestAudioPlayer(), 300, 300);
}
