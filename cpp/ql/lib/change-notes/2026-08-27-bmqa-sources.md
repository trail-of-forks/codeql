---
category: minorAnalysis
---
* Added the BlazingMQ consumer-side message accessors (`BloombergLP::bmqa`) as remote flow sources. A consumed message's payload (`bmqa::Message::getData`) and its properties (`bmqa::MessageProperties::getPropertyAsString`, `getPropertyAsInt32`, and the other `getPropertyAs*` accessors) are now treated as attacker-controlled input from the broker.
