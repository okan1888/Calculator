#if !defined serial_h
#define serial_h


class Serializer;  //forward declration
class DeSerializer;

class Serializable 
//abstract class;other classes inherits this to make themselves serializable
{
public:
	virtual void Serialize(Serializer &out) const = 0; //pure virtual functions
	virtual void DeSerialize(DeSerializer &in) = 0;
};
#endif

