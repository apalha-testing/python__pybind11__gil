#include <string>
#include <memory>
#include <omp.h>
#include <unistd.h>
#include <iostream>

#define THREAD_NUM 4

#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

namespace autos {

enum EngineType {
    TWO_STROKE = 0,
    FOUR_STROKE = 1
};

class Motorcycle {

private:

    /// Name
    std::string _name;

public:

    /// Shared pointer constructor
    static std::shared_ptr<Motorcycle> create(std::string name);

    /// Constructor
    Motorcycle(std::string name);

    /// Get name
    /// @return Name
    std::string get_name() const;

    /// Ride the bike
    /// @param road Name of the road
    void ride(std::string road) const;

    /// Get engine type
    /// @return Engine type
    EngineType get_engine_type() const;
};

class Photograph {

public:

    /// Constructor/destructor
    virtual ~Photograph() {};

    /// Pure virtual method
    /// @param bike Bike
    /// @return true if beautiful
    virtual bool is_beautiful(std::shared_ptr<Motorcycle> bike) const = 0;

    virtual double get_exposure(double value) const = 0;
};

class PhotographFancy {

public:
    Photograph *photo;
    PhotographFancy(Photograph *photoInput){
        this->photo = photoInput;
    };

    double get_double_exposure(double value){
      omp_set_num_threads(THREAD_NUM);
      #pragma omp parallel
      {
        usleep(5000 * omp_get_num_threads()); // do this to avoid race condition while printing
        std::cout << "Number of available threads: " << omp_get_num_threads() << std::endl;
        // each thread can also get its own number
        std::cout << "Current thread number: " << omp_get_thread_num() << std::endl;
        std::cout << "Hello, World! " << this->photo->get_exposure(value) + this->photo->get_exposure(value) << "\n"<< std::endl;
      }
      return 1.0;
    };
};

}

#endif
