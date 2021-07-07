#include "csp/csp.hh"
// our application errors must be defined before Ex.hh
#include "csp/IPV4Socket.hh"
#include "csp/XDLRequest.hh"
#include "opengl/GLWin.hh"
#include "xdl/List.hh"
//#include "XDLServlet.hh"
#include <cstdlib>
using namespace std;

Log srvlog;  // log all important events for security and debugging

class StockQuote {
 public:
  float open, high, low, close;
  StockQuote(float open, float high, float low, float close)
      : open(open), high(high), low(low), close(close) {}
  void write(Buffer& buf) const {
    buf.write(open);
    buf.write(high);
    buf.write(low);
    buf.write(close);
  }
  void writeMeta(Buffer& buf) const {
    buf.write("StockQuote");
    buf.write(4);
    buf.write(DataType::F32);
    buf.write("open");
    buf.write(DataType::F32);
    buf.write("high");
    buf.write(DataType::F32);
    buf.write("low");
    buf.write(DataType::F32);
    buf.write("close");
  }
};

int main(int argc, char* argv[]) {
  int port = argc > 1 ? atoi(argv[1]) : 8060;
  GLWin::classInit();
  try {
    IPV4Socket s(port);
    List<const StockQuote> quotes;
    for (int i = 0; i < 100; i++) {
      quotes.add(StockQuote(i, i, i, i));
    }
    XDLRequest req(&quotes);
    s.attach(&req);
    s.wait();  // main server wait loop
  } catch (const Ex& e) {
    cerr << e << '\n';
  }
  GLWin::classCleanup();
  return 0;
}
