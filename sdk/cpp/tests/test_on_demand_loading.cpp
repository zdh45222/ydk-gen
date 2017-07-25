/// YANG Development Kit
// Copyright 2017 Cisco Systems. All rights reserved
//
////////////////////////////////////////////////////////////////
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
//////////////////////////////////////////////////////////////////

#include <string>
#include "../src/path_api.hpp"
#include "../core/src/netconf_provider.hpp"
#include "config.hpp"
#include "catch.hpp"

using namespace ydk;

std::string AUGMENTED_XML_PAYLOAD = R"(<cpython xmlns="http://cisco.com/ns/yang/ietf-aug-base-1">
  <doc>
    <aug-5-identityref xmlns="http://cisco.com/ns/yang/yaug-five">aug-identity</aug-5-identityref>
    <disutils>
      <four-aug-list xmlns="http://cisco.com/ns/yang/yaug-four">
        <enabled>true</enabled>
      </four-aug-list>
    </disutils>
    <ydktest-aug-4 xmlns="http://cisco.com/ns/yang/yaug-four">
      <aug-four>aug four</aug-four>
    </ydktest-aug-4>
    <ydktest-aug-1 xmlns="http://cisco.com/ns/yang/yaug-one">
      <aug-one>aug one</aug-one>
    </ydktest-aug-1>
    <ydktest-aug-2 xmlns="http://cisco.com/ns/yang/yaug-two">
      <aug-two>aug two</aug-two>
    </ydktest-aug-2>
  </doc>
  <lib>
    <ydktest-aug-4 xmlns="http://cisco.com/ns/yang/yaug-four">
      <ydktest-aug-nested-4>
        <aug-four>aug four</aug-four>
      </ydktest-aug-nested-4>
    </ydktest-aug-4>
    <ydktest-aug-1 xmlns="http://cisco.com/ns/yang/yaug-one">
      <ydktest-aug-nested-1>
        <aug-one>aug one</aug-one>
      </ydktest-aug-nested-1>
    </ydktest-aug-1>
    <ydktest-aug-2 xmlns="http://cisco.com/ns/yang/yaug-two">
      <ydktest-aug-nested-2>
        <aug-two>aug two</aug-two>
      </ydktest-aug-nested-2>
    </ydktest-aug-2>
  </lib>
</cpython>)";

std::string AUGMENTED_JSON_PAYLOAD = R"({
  "ietf-aug-base-1:cpython": {
    "doc": {
      "disutils": {
        "ydktest-aug-ietf-4:four-aug-list": {
          "enabled": true
        }
      },
      "ydktest-aug-ietf-4:ydktest-aug-4": {
        "aug-four": "aug four"
      },
      "ydktest-aug-ietf-1:ydktest-aug-1": {
        "aug-one": "aug one"
      },
      "ydktest-aug-ietf-2:ydktest-aug-2": {
        "aug-two": "aug two"
      },
      "aug-5-identityref": "ydktest-aug-ietf-5:aug-identity"
    },
    "lib": {
      "ydktest-aug-ietf-4:ydktest-aug-4": {
        "ydktest-aug-nested-4": {
          "aug-four": "aug four"
        }
      },
      "ydktest-aug-ietf-1:ydktest-aug-1": {
        "ydktest-aug-nested-1": {
          "aug-one": "aug one"
        }
      },
      "ydktest-aug-ietf-2:ydktest-aug-2": {
        "ydktest-aug-nested-2": {
          "aug-two": "aug two"
        }
      }
    }
  }
}
)";

TEST_CASE("on_demand_loading_json")
{
    ydk::path::Repository repo{TEST_HOME};
    NetconfServiceProvider provider{repo, "127.0.0.1", "admin", "admin", 12022};
    auto & root_schema = provider.get_root_schema();
    ydk::path::Codec codec{};

    auto cpython = codec.decode(root_schema, AUGMENTED_JSON_PAYLOAD, ydk::EncodingFormat::JSON);
    REQUIRE(cpython);
}

TEST_CASE("on_demand_loading_xml")
{
    ydk::path::Repository repo{TEST_HOME};
    NetconfServiceProvider provider{repo, "127.0.0.1", "admin", "admin", 12022};
    auto & root_schema = provider.get_root_schema();
    ydk::path::Codec codec{};

    auto cpython = codec.decode(root_schema, AUGMENTED_XML_PAYLOAD, ydk::EncodingFormat::XML);
    REQUIRE(cpython);
}
