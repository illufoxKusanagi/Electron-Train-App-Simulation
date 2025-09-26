"use client";

import { AppSidebar } from "@/components/app-sidebar";
import { ModeToggle } from "@/components/toggle-mode-button";
import { Form } from "@/components/ui/form";
import { SidebarProvider, SidebarTrigger } from "@/components/ui/sidebar";
import { useForm } from "react-hook-form";
import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";
import { toast } from "sonner";
import { Button } from "@/components/ui/button";
import { useState } from "react";
import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { InputWidget } from "@/components/inputs/input-widget";
import {
  CalculatedMassFormSchema,
  calculatedMassRows,
  carMassFormRows,
  carPassangerFormRows,
  carTypeFormRows,
  constantFormRows,
  ConstantFormSchema,
  trainsetFormRows,
  TrainsetFormSchema,
} from "./form.constant";

export default function Main() {
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [csvData, setCsvData] = useState<Record<string, number[][]>>({});

  const constantForm = useForm<z.infer<typeof ConstantFormSchema>>({
    resolver: zodResolver(ConstantFormSchema),
    defaultValues: {
      i_T: 1.05,
      i_M: 1.1,
      n_axle: 4,
      n_tm: 24,
      wheelDiameter: 860,
      mass_P: 70,
      gearRatio: 3,
      load: 0,
      carLength: 20,
      loadCondition: "AW4",
    },
  });

  const trainsetForm = useForm<z.infer<typeof TrainsetFormSchema>>({
    resolver: zodResolver(TrainsetFormSchema),
    defaultValues: {
      n_car: 12,
      n_M1: 2,
      n_M2: 2,
      n_Tc: 2,
      n_T1: 2,
      n_T2: 2,
      n_T3: 2,
      n_M1_disabled: 0,
      n_M2_disabled: 0,
      mass_M1: 20,
      mass_M2: 20,
      mass_Tc: 10,
      mass_T1: 10,
      mass_T2: 10,
      mass_T3: 10,
      n_PM1: 200,
      n_PM2: 200,
      n_PTc: 100,
      n_PT1: 200,
      n_PT2: 200,
      n_PT3: 200,
    },
  });

  const calculatedMassForm = useForm<z.infer<typeof CalculatedMassFormSchema>>({
    resolver: zodResolver(CalculatedMassFormSchema),
    defaultValues: {
      mass_totalEmpty: 180,
      mass_totalLoad: 334,
      mass_totalInertial: 349,
    },
  });

  const handleFileLoad = (name: string, data: number[][]) => {
    setCsvData((prev) => ({
      ...prev,
      [name]: data,
    }));
    console.log(`File loaded for ${name}:`, data);
  };

  async function onSubmit(data: z.infer<typeof ConstantFormSchema>) {
    setIsSubmitting(true);
    try {
      console.log("Form Data:", data);
      console.log("CSV Data:", csvData);

      toast("Data berhasil disimpan!", {
        description: (
          <pre className="mt-2 w-[320px] rounded-md bg-neutral-950 p-4">
            <code className="text-white">{JSON.stringify(data, null, 2)}</code>
          </pre>
        ),
      });
    } catch (error) {
      toast("Error!", {
        description: "Gagal menyimpan data. Silakan coba lagi.",
      });
    } finally {
      setIsSubmitting(false);
    }
  }

  async function onTrainsetSubmit(data: z.infer<typeof TrainsetFormSchema>) {
    setIsSubmitting(true);
    try {
      console.log("Form Data:", data);
      console.log("CSV Data:", csvData);

      toast("Data berhasil disimpan!", {
        description: (
          <pre className="mt-2 w-[320px] rounded-md bg-neutral-950 p-4">
            <code className="text-white">{JSON.stringify(data, null, 2)}</code>
          </pre>
        ),
      });
    } catch (error) {
      toast("Error!", {
        description: "Gagal menyimpan data. Silakan coba lagi.",
      });
    } finally {
      setIsSubmitting(false);
    }
  }

  const handleReset = () => {
    constantForm.reset();
    setCsvData({});
    toast("Form berhasil direset!");
  };

  return (
    <SidebarProvider defaultOpen={false}>
      {/* Sticky Top Bar */}
      <div className="flex flex-col w-full">
        <div className="sticky top-0 z-50 bg-background/95 backdrop-blur supports-[backdrop-filter]:bg-background/60 border-b border-border">
          <AppSidebar />
          <div className="flex items-center justify-between px-4 py-3">
            <SidebarTrigger size="lg" />
            <ModeToggle />
          </div>
        </div>

        <div className="flex flex-col xl:flex-row gap-4 w-full justify-start xl:justify-center items-center p-12 overflow-auto">
          <Card className="px-6 py-8 max-h-[45rem] min-h-[40rem] h-full w-full max-w-2xl rounded-3xl justify-center">
            <CardHeader className="text-center">
              <CardTitle className="text-2xl">
                Train Constant Parameter
              </CardTitle>
              <CardDescription>
                Input related to Train and Car configuration
              </CardDescription>
            </CardHeader>
            <CardContent>
              <Form {...constantForm}>
                <form
                  onSubmit={constantForm.handleSubmit(onSubmit)}
                  className="space-y-6"
                >
                  <div className="flex flex-col gap-6">
                    {constantFormRows.map((row, rowIndex) => (
                      <div key={rowIndex} className="grid grid-cols-3 gap-4">
                        {row.map((inputType) => (
                          <InputWidget
                            key={inputType.name}
                            inputType={inputType}
                            control={constantForm.control}
                            onFileLoad={handleFileLoad}
                          />
                        ))}
                        {row.length < 3 &&
                          Array.from({ length: 3 - row.length }).map(
                            (_, emptyIndex) => (
                              <div key={`empty-${rowIndex}-${emptyIndex}`} />
                            )
                          )}
                      </div>
                    ))}
                  </div>

                  <div className="flex gap-4 pt-4">
                    <Button
                      type="submit"
                      className="flex-1"
                      disabled={isSubmitting}
                    >
                      {isSubmitting ? "Menyimpan..." : "Save Data"}
                    </Button>
                    <Button
                      type="button"
                      variant="outline"
                      className="flex-1"
                      onClick={handleReset}
                    >
                      Reset
                    </Button>
                  </div>
                </form>
              </Form>
            </CardContent>
          </Card>
          <Card className="px-2 py-8 max-h-[45rem] min-h-[40rem] w-full max-w-2xl rounded-3xl overflow-auto">
            <CardHeader className="text-center">
              <CardTitle className="text-2xl">Trainset Inputs</CardTitle>
              <CardDescription>
                Related to trainset configuration and car information
              </CardDescription>
            </CardHeader>
            <CardContent>
              <Form {...trainsetForm}>
                <form
                  onSubmit={trainsetForm.handleSubmit(onTrainsetSubmit)}
                  className="space-y-6"
                >
                  {trainsetFormRows.map((row, rowIndex) => (
                    <div
                      key={rowIndex}
                      className="flex flex-row gap-4 justify-start"
                    >
                      {row.map((inputType) => (
                        <InputWidget
                          key={inputType.name}
                          inputType={inputType}
                          control={trainsetForm.control}
                          onFileLoad={handleFileLoad}
                        />
                      ))}
                      <div
                        className="flex
                      container w-4xl h-28 border rounded-lg hover:bg-accent
                      hover:text-accent-foreground dark:bg-input/30 dark:border-input
                      dark:hover:bg-input/50 justify-center items-center"
                      >
                        <p>lorem ipsum</p>
                      </div>
                    </div>
                  ))}
                  <Card>
                    <CardHeader>
                      <CardTitle className="text-center">
                        Calcualted Mass
                      </CardTitle>
                    </CardHeader>
                    <CardContent>
                      {calculatedMassRows.map((row, rowIndex) => (
                        <div
                          key={rowIndex}
                          className="flex flex-row gap-4 justify-center"
                        >
                          {row.map((inputType) => (
                            <InputWidget
                              key={inputType.name}
                              inputType={inputType}
                              control={calculatedMassForm.control}
                              onFileLoad={handleFileLoad}
                            />
                          ))}
                        </div>
                      ))}
                    </CardContent>
                  </Card>
                  <div className="flex flex-row gap-2">
                    <Card>
                      <CardHeader>
                        <CardTitle className="text-center">
                          Car number
                        </CardTitle>
                      </CardHeader>
                      <CardContent>
                        {carTypeFormRows.map((row, rowIndex) => (
                          <div
                            key={rowIndex}
                            className="flex flex-col gap-4 justify-start"
                          >
                            {row.map((inputType) => (
                              <InputWidget
                                key={inputType.name}
                                inputType={inputType}
                                control={trainsetForm.control}
                                onFileLoad={handleFileLoad}
                              />
                            ))}
                          </div>
                        ))}
                      </CardContent>
                    </Card>
                    <Card>
                      <CardHeader>
                        <CardTitle className="text-center">
                          Car Passenger
                        </CardTitle>
                      </CardHeader>
                      <CardContent>
                        {carPassangerFormRows.map((row, rowIndex) => (
                          <div
                            key={rowIndex}
                            className="flex flex-col gap-4 justify-start"
                          >
                            {row.map((inputType) => (
                              <InputWidget
                                key={inputType.name}
                                inputType={inputType}
                                control={trainsetForm.control}
                                onFileLoad={handleFileLoad}
                              />
                            ))}
                          </div>
                        ))}
                      </CardContent>
                    </Card>
                    <Card>
                      <CardHeader>
                        <CardTitle className="text-center">Car Mass</CardTitle>
                      </CardHeader>
                      <CardContent>
                        {carMassFormRows.map((row, rowIndex) => (
                          <div
                            key={rowIndex}
                            className="flex flex-col gap-4 justify-start"
                          >
                            {row.map((inputType) => (
                              <InputWidget
                                key={inputType.name}
                                inputType={inputType}
                                control={trainsetForm.control}
                                onFileLoad={handleFileLoad}
                              />
                            ))}
                          </div>
                        ))}
                      </CardContent>
                    </Card>
                  </div>

                  <div className="flex gap-4 pt-4">
                    <Button
                      type="submit"
                      className="flex-1"
                      disabled={isSubmitting}
                    >
                      {isSubmitting ? "Menyimpan..." : "Save Data"}
                    </Button>
                    <Button
                      type="button"
                      variant="outline"
                      className="flex-1"
                      onClick={handleReset}
                    >
                      Reset
                    </Button>
                  </div>
                </form>
              </Form>
            </CardContent>
          </Card>
        </div>
      </div>
    </SidebarProvider>
  );
}
