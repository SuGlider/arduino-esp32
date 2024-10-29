#include <sdkconfig.h>
#ifdef CONFIG_ESP_MATTER_ENABLE_DATA_MODEL

#include <Matter.h>
#include <app/server/Server.h>
#include <MatterEndpoints/MatterDimmableLight.h>

using namespace esp_matter;
using namespace esp_matter::endpoint;
using namespace chip::app::Clusters;

bool MatterDimmableLight::attributeChangeCB(uint16_t endpoint_id, uint32_t cluster_id, uint32_t attribute_id, esp_matter_attr_val_t *val) {
  bool ret = true;
  if (!started) {
    log_e("Matter DimmableLight device has not begun.");
    return false;
  }

  log_d("Dimmable Attr update callback: endpoint: %u, cluster: %u, attribute: %u, val: %u", endpoint_id, cluster_id, attribute_id, val->val.u32);

  if (endpoint_id == getEndPointId()) {
    switch(cluster_id) {
      case OnOff::Id:
        if (attribute_id == OnOff::Attributes::OnOff::Id) {
          if (_onChangeOnOffCB != NULL) {
            ret = _onChangeOnOffCB(val->val.b);
            log_d("DimmableLight On/Off State changed to %d", val->val.b);
            if (ret == true) {
              onOffState = val->val.b;
            }
          }
        }
        break;
      case LevelControl::Id:
        if (attribute_id == LevelControl::Attributes::CurrentLevel::Id) {
          if (_onChangeBrightnessCB != NULL) {
            ret = _onChangeBrightnessCB(val->val.u8);
            log_d("DimmableLight Brightness changed to %d", val->val.u8);
            if (ret == true) {
              brightnessLevel = val->val.u8;
            }
          }
        }
        break;  
    }
  }
  return ret;
}

MatterDimmableLight::MatterDimmableLight() {}

MatterDimmableLight::~MatterDimmableLight() {
  end();
}

bool MatterDimmableLight::begin(bool initialState, uint8_t brightness) {
  ArduinoMatter::_init();
  dimmable_light::config_t light_config;

  light_config.on_off.on_off = initialState;
  light_config.on_off.lighting.start_up_on_off = nullptr;
  onOffState = initialState;

  light_config.level_control.current_level = brightness;
  light_config.level_control.lighting.start_up_current_level = nullptr;
  brightnessLevel = brightness;

  // endpoint handles can be used to add/modify clusters.
  endpoint_t *endpoint = dimmable_light::create(node::get(), &light_config, ENDPOINT_FLAG_NONE, (void *)this);
  if (endpoint == nullptr) {
    log_e("Failed to create dimmable light endpoint");
    return false;
  }

  setEndPointId(endpoint::get_id(endpoint));
  log_i("Dimmable Light created with endpoint_id %d", getEndPointId());
  started = true;
  return true;
}

void MatterDimmableLight::end() {
  started = false;
}

bool MatterDimmableLight::setOnOff(bool newState) {
  if (!started) {
    log_e("Matter Dimmable Light device has not begun.");
    return false;
  }

  // avoid processing the a "no-change"
  if (onOffState == newState) {
    return true;
  }

  onOffState = newState;

  endpoint_t *endpoint = endpoint::get(node::get(), endpoint_id);
  cluster_t *cluster = cluster::get(endpoint, OnOff::Id);
  attribute_t *attribute = attribute::get(cluster, OnOff::Attributes::OnOff::Id);

  esp_matter_attr_val_t val = esp_matter_invalid(NULL);
  attribute::get_val(attribute, &val);

  if (val.val.b != onOffState) {
    val.val.b = onOffState;
    attribute::update(endpoint_id, OnOff::Id, OnOff::Attributes::OnOff::Id, &val);
  }
  return true;
}

bool MatterDimmableLight::getOnOff() {
  return onOffState;
}

bool MatterDimmableLight::toggle() {
  return setOnOff(!onOffState);
}

bool MatterDimmableLight::setBrightness(uint8_t newBrightness) {
  if (!started) {
    log_w("Matter Dimmable Light device has not begun.");
    return false;
  }

  // avoid processing the a "no-change"
  if (brightnessLevel == newBrightness) {
    return true;
  }

  brightnessLevel = newBrightness;

  endpoint_t *endpoint = endpoint::get(node::get(), endpoint_id);
  cluster_t *cluster = cluster::get(endpoint, LevelControl::Id);
  attribute_t *attribute = attribute::get(cluster, LevelControl::Attributes::CurrentLevel::Id);

  esp_matter_attr_val_t val = esp_matter_invalid(NULL);
  attribute::get_val(attribute, &val);

  if (val.val.u8 != brightnessLevel) {
    val.val.u8 = brightnessLevel;
    attribute::update(endpoint_id, LevelControl::Id, LevelControl::Attributes::CurrentLevel::Id, &val);
  }
  return true;
}

uint8_t MatterDimmableLight::getBrightness() {
  return brightnessLevel;
}

MatterDimmableLight::operator bool() {
  return getOnOff();
}

void MatterDimmableLight::operator=(bool newState) {
  setOnOff(newState);
}
#endif /* CONFIG_ESP_MATTER_ENABLE_DATA_MODEL */
