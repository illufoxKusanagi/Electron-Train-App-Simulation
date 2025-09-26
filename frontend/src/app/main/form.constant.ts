import z from "zod";
import { InputType } from "../../../types/input-types";

const chunkArray = <T>(array: T[], chunkSize: number): T[][] => {
  const chunks: T[][] = [];
  for (let i = 0; i < array.length; i += chunkSize) {
    chunks.push(array.slice(i, i + chunkSize));
  }
  return chunks;
};

export const TrainsetFormSchema = z.object({
  n_car: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_M1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_M2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_Tc: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_T1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_T2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_T3: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_M1_disabled: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_M2_disabled: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_M1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_M2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_Tc: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_T1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_T2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  mass_T3: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PM1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PM2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PTc: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PT1: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PT2: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
  n_PT3: z.coerce.number<number>({
    message: "This Value must be a number",
  }),
});
export const ConstantFormSchema = z.object({
  i_T: z.coerce.number<number>({
    message: "iCt Must be a number or decimal",
  }),
  i_M: z.coerce.number<number>({
    message: "iCm Must be a number or decimal",
  }),
  n_axle: z.coerce.number<number>({
    message: "Number of Axle must be a number",
  }),
  n_tm: z.coerce.number<number>({
    message: "Number of Traction Motor must be a number",
  }),
  wheelDiameter: z.coerce.number<number>({
    message: "Wheel Diameter must be a number",
  }),
  mass_P: z.coerce.number<number>({
    message: "Passenger Weight must be a number",
  }),
  gearRatio: z.coerce.number<number>({
    message: "Gear Ratio must be a number",
  }),
  load: z.coerce.number<number>({
    message: "Load per car must be a number",
  }),
  carLength: z.coerce.number<number>({
    message: "Car Length must be a number",
  }),
  loadCondition: z.enum(["AW0", "AW1", "AW2", "AW3", "AW4"], {
    message: "Load Condition must be one of AW0, AW1, AW2, AW3, AW4",
  }),
});
export const CalculatedMassFormSchema = z.object({
  mass_totalEmpty: z.coerce.number<number>(),
  mass_totalLoad: z.coerce.number<number>(),
  mass_totalInertial: z.coerce.number<number>(),
});
export const constantInputFormDatas: InputType[] = [
  {
    label: "Inertial Coefficient Trailer",
    unit: "",
    type: "field",
    name: "i_T",
  },
  {
    label: "Inertial Coefficient Motor",
    unit: "",
    type: "field",
    name: "i_M",
  },
  {
    label: "Number of Axle",
    unit: "",
    type: "field",
    name: "n_axle",
  },
  {
    label: "Number of Traction Motor",
    unit: "",
    type: "field",
    name: "n_tm",
  },
  {
    label: "Wheel Diameter",
    unit: "mm",
    type: "field",
    name: "wheelDiameter",
  },
  {
    label: "Passenger Weight",
    unit: "kg",
    type: "field",
    name: "mass_P",
  },
  {
    label: "Gear Ratio",
    unit: "",
    type: "field",
    name: "gearRatio",
  },
  {
    label: "Load per Car",
    unit: "ton",
    type: "field",
    name: "load",
  },
  {
    label: "Car Length",
    unit: "m",
    type: "field",
    name: "carLength",
  },
  {
    label: "Load Condition",
    unit: "",
    type: "dropdown",
    name: "loadCondition",
    options: ["AW0", "AW1", "AW2", "AW3", "AW4"],
  },
];

const trainsetInputFormDatas: InputType[] = [
  {
    label: "n_car",
    unit: "",
    type: "dropdown",
    name: "n_car",
    options: ["12", "10", "8", "6", "4", "12-Degraded", "10-Degraded"],
  },
];
const carTypeFormDatas: InputType[] = [
  { label: "M1", unit: "car", type: "field", name: "n_M1" },
  { label: "M2", unit: "car", type: "field", name: "n_M2" },
  { label: "Tc", unit: "car", type: "field", name: "n_Tc" },
  { label: "T1", unit: "car", type: "field", name: "n_T1" },
  { label: "T2", unit: "car", type: "field", name: "n_T2" },
  { label: "T3", unit: "car", type: "field", name: "n_T3" },
  { label: "M1-Deg", unit: "car", type: "field", name: "n_M1_disabled" },
  { label: "M2-Deg", unit: "car", type: "field", name: "n_M2_disabled" },
];
const carPassangerFormDatas: InputType[] = [
  { label: "M1", unit: "person", type: "field", name: "n_PM1" },
  { label: "M2", unit: "person", type: "field", name: "n_PM2" },
  { label: "Tc", unit: "person", type: "field", name: "n_PTc" },
  { label: "T1", unit: "person", type: "field", name: "n_PT1" },
  { label: "T2", unit: "person", type: "field", name: "n_PT2" },
  { label: "T3", unit: "person", type: "field", name: "n_PT3" },
];
const carMassFormDatas: InputType[] = [
  { label: "M1", unit: "ton", type: "field", name: "mass_M1" },
  { label: "M2", unit: "ton", type: "field", name: "mass_M2" },
  { label: "Tc", unit: "ton", type: "field", name: "mass_Tc" },
  { label: "T1", unit: "ton", type: "field", name: "mass_T1" },
  { label: "T2", unit: "ton", type: "field", name: "mass_T2" },
  { label: "T3", unit: "ton", type: "field", name: "mass_T3" },
];
const calculatedMassDatas: InputType[] = [
  {
    label: "Empty Mass Car",
    unit: "ton",
    type: "field",
    name: "mass_totalEmpty",
    isReadOnly: true,
  },
  {
    label: "Loaded Mass Car",
    unit: "ton",
    type: "field",
    name: "mass_totalLoad",
    isReadOnly: true,
  },
  {
    label: "Inertial Mass Car",
    unit: "ton",
    type: "field",
    name: "mass_totalInertial",
    isReadOnly: true,
  },
];

export const constantFormRows = chunkArray(constantInputFormDatas, 3);
export const trainsetFormRows = chunkArray(trainsetInputFormDatas, 3);
export const carMassFormRows = chunkArray(carMassFormDatas, 3);
export const carPassangerFormRows = chunkArray(carPassangerFormDatas, 3);
export const carTypeFormRows = chunkArray(carTypeFormDatas, 3);
export const calculatedMassRows = chunkArray(calculatedMassDatas, 3);
