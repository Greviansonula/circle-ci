#include <iostream>
#include <datastax/cassandra.hpp>

class AstraDB {
public:
  AstraDB(const std::string& contact_points, int port)
    : contact_points_(contact_points), port_(port), cluster_(cass::Cluster::build()
      .set_contact_points(contact_points)
      .set_port(port)
      .finalize()) {}
  ~AstraDB() { session_.close(); }

  void Connect() { session_ = cluster_.connect(); }

  void ExecuteQuery(const std::string& query) {
    result_ = session_.execute(query);
  }

  void PrintResults() {
    for (const auto& row : result_) {
      std::cout << row.get_string("cluster_name") << std::endl;
    }
  }

private:
  std::string contact_points_;
  int port_;
  cass::Cluster cluster_;
  cass::Session session_;
  cass::Result result_;
};

int main() {
  AstraDB db("127.0.0.1", 9042);
  db.Connect();
  db.ExecuteQuery("SELECT * FROM system.local");
  db.PrintResults();
  return 0;
}
