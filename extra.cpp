// Decide on which shared_ptr to use: boost::shared_ptr or std::shared_ptr
#if __cplusplus > 199711L
namespace MyProject
{
    typedef shared_ptr std::shared_ptr
}
#else
#include <boost/shared_ptr.hpp>
namespace MyProject
{
    typedef shared_ptr boost::shared_ptr
}
#endif


#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <queue>

using namespace std;

/*
	A simple string tokenizing method
*/
template<class T>
void tokenizeV(const std::string& s, std::vector<T>& v)
{
	typedef boost::tokenizer::<boost::escaped_list_separator<char> > tokne_t;
	
	token_t token(s);
	for (token_t::iterator it(token.begin()); it != token.end(); ++it) {
		string f(*it);
		boost::trim(f);
		v.push_back(boost::lexical_cast<T>(f));
	}
}

/*
	Implementation of Simple Moving Average
*/
template<typename T, int N>
class MovingAverage
{
public:
	MovingAverage(): num_samples_(0), total_(0) {}
	~MovingAverage();
	void operator(T& sample)
	{
		if (num_samples_ < N) {
			samples_.push_back(sample);
			total_ += sample;
		} else {
			total_ -= samples_.pop_front();
			samples_.push_back(sample);
			total_ += sample;
		}
	}
	
	operator double() const
	{
		// return total_ / std::min(num_samples_, N);
		return total_ / num_samples_;
	}
	
private:
	std::queue<T> samples_[N];
	int num_samples_;
	T total_;
};

template<typename T, int N>
class ExponentialMovingAverage: public MovingAverage
{
	void operator(T& sample)
	{
		
	}
};