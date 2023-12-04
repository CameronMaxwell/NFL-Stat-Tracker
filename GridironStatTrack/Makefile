
CXX=g++
WT_BASE=/usr/local
CXXFLAGS=--std=c++14 -I$(WT_BASE)/include 
LDFLAGS=-L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt

# Identify our code base to be building.  Headers are listed under DEPS, and objects under OBJS.

DEPS = GridironApplication.h LoginWidget.h RegisterWidget.h JsonDataManager.h Leaderboard.h HelpPage.h User.h BettingTrack.h Bets.h ComparisonTool.h FavouritesWidget.h 
OBJS = Main.o GridironApplication.o LoginWidget.o RegisterWidget.o JsonDataManager.o Leaderboard.o HelpPage.o User.o BettingTrack.o Bets.o ComparisonTool.o FavouritesWidget.o 

# How do we build objects?

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# How do we build the executable?

gridiron: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# How do we clean up after ourselves?

clean:
	rm -f gridiron $(OBJS)


