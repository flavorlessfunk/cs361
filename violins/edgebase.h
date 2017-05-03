#ifndef EDGEBASE_H
#define EDGEBASE_H

struct EdgeBase
{
  bool occupied;
  unsigned source, dest;

  EdgeBase() : occupied(false) {}

  bool operator== (const EdgeBase& eb) const
  {return (source == eb.source) && (dest == eb.dest);}
};

#endif

