#pragma once

class ActorComponent :
	public Ref
{
public:
	ActorComponent();
	virtual ~ActorComponent();

	static ActorComponent*	create();
	bool					init();
};